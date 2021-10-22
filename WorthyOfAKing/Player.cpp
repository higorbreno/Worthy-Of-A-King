#include "Player.h"
#include "Enums.h"
#include "Block.h"
#include "Level.h"

const double Player::PIXEL_PER_METER = 50;
Vector Player::gravity = Vector();
Vector Player::jumpForce = Vector();
TileSet* Player::tileSet = nullptr;

Player::Player()
{
	gravity.setXY(0, 50.0f);
	jumpForce.setXY(0, -900.0f);

	if (tileSet == nullptr)
		tileSet = new TileSet("Resources/PlayerSpriteSheet.png", 64, 64, 23, 46);

	type = ObjTypes::PLAYER;
	velx = 4;
	isClimbing = false;
	hasZeroGravity = false;
	isMovingLeft = false;
	mass = 100;
	inverseMass = 1 / mass;

	forceAccum = new Vector();
	velocity = new Vector();

	anim = new Animation(tileSet, 0.120f, true);

	uint seqIdle[1] = { 0 };
	uint seqIdleLeft[1] = { 45 };
	uint seqWalk[4] = { 0,1,2,3 };
	uint seqWalkLeft[4] = { 45,44,43,42 };
	uint seqJump[4] = { 4,5,6,7 };
	uint seqJumpLeft[4] = { 41,40,39,38 };
	uint seqHit[3] = { 8,9,8 };
	uint seqHitLeft[3] = { 37,36,37 };
	uint seqSlash[3] = { 10,11,12 };
	uint seqSlashLeft[3] = { 35,34,33 };
	uint seqPunch[2] = { 13,11 };
	uint seqPunchLeft[2] = { 32,34 };
	uint seqRun[4] = { 14,15,16,17 };
	uint seqRunLeft[4] = { 31,30,29,28 };
	uint seqClimb[4] = { 18,19,20,21 };
	uint seqClimbLeft[4] = { 27,26,25,24 };

	anim->Add(IDLE, seqIdle, 1);
	anim->Add(IDLELEFT, seqIdleLeft, 1);
	anim->Add(WALK, seqWalk, 4);
	anim->Add(WALKLEFT, seqWalkLeft, 4);
	anim->Add(JUMP, seqJump, 4);
	anim->Add(JUMPLEFT, seqJumpLeft, 4);
	anim->Add(HIT, seqHit, 3);
	anim->Add(HITLEFT, seqHitLeft, 3);
	anim->Add(SLASH, seqSlash, 3);
	anim->Add(SLASHLEFT, seqSlashLeft, 3);
	anim->Add(PUNCH, seqPunch, 2);
	anim->Add(PUNCHLEFT, seqPunchLeft, 2);
	anim->Add(RUN, seqRun, 4);
	anim->Add(RUNLEFT, seqRunLeft, 4);
	anim->Add(CLIMB, seqClimb, 4);
	anim->Add(CLIMBLEFT, seqClimbLeft, 4);

	state = IDLE;

	BBox(new Rect(-10.0f, -16.0f, 10.0f, 32.0f));
}

Player::~Player()
{
	delete tileSet;
	tileSet = nullptr;
	delete anim;
	delete forceAccum;
	delete velocity;
}

void Player::Update()
{
	hasZeroGravity = false;

	if (window->KeyDown('A') || window->KeyDown(VK_LEFT)) {
		state = RUN;
		isMovingLeft = true;
		Translate(-velx * PIXEL_PER_METER * gameTime, 0);
	}
	if (window->KeyDown('D') || window->KeyDown(VK_RIGHT)) {
		state = RUN;
		isMovingLeft = false;
		Translate(velx * PIXEL_PER_METER * gameTime, 0);
	}

	if (state % 2 == 0) {
		if (isMovingLeft)
			++state;
	}
	else if (!isMovingLeft) {
		--state;
	}

	applyForce(&gravity);
	*velocity = *forceAccum * inverseMass;
	

	Translate(velocity->X() * PIXEL_PER_METER * gameTime, velocity->Y() * PIXEL_PER_METER * gameTime);

	anim->Select(state);

	if (y > 1000)
		Level::isGameOver = true;

	if (!isClimbing) {
		if (isMovingLeft)
			state = IDLELEFT;
		else
			state = IDLE;
		anim->NextFrame();
	}
	//Game::camera->MoveTo(x - window->CenterX(), 0);
}

void Player::OnCollision(Object* obj)
{
	if (obj->Type() == ObjTypes::BLOCK) {
		Block* block = (Block*)obj;
		if (block->blockType == BlockType::SOLID) {
			bool isLeft = (x - obj->X()) < 0;
			bool isTop = (y - obj->Y()) < 0;

			float dx, dy;

			Rect* player = (Rect*)BBox();
			Rect* block = (Rect*)obj->BBox();

			if (isTop)
				dy = block->Top() - player->Bottom();
			else
				dy = block->Bottom() - player->Top();

			if (isLeft)
				dx = block->Left() - player->Right();
			else
				dx = block->Right() - player->Left();

			if (abs(dx) <= abs(dy)) {
				Translate(dx, 0);
			}
			else {
				Translate(0, dy);
				if (isTop && !hasZeroGravity)
					zeroGravityForce();
				if (!isTop)
					zeroGravityForce();
				else if (isClimbing)
					isClimbing = false;
				if (window->KeyPress(VK_SPACE) && isTop) {
					zeroGravityForce();
					applyForce(&jumpForce);
				}
			}
		}
		else if (block->blockType == BlockType::STAIR) {
			zeroGravityForce();
			if (window->KeyDown('W') || window->KeyDown(VK_UP)) {
				state = CLIMB;
				isClimbing = true;
				MoveTo(block->X(), y);
				Translate(0, -100 * gameTime);
				anim->NextFrame();
			}
			if (window->KeyDown('S') || window->KeyDown(VK_DOWN)) {
				state = CLIMB;
				isClimbing = true;
				MoveTo(block->X(), y);
				Translate(0, 100 * gameTime);
				anim->NextFrame();
			}
		}
	}
	else if (obj->Type() == ObjTypes::OBSTACLE) {
		Level::isGameOver = true;
	}
	else if (obj->Type() == ObjTypes::ENEMY) {
		bool isLeft = (x - obj->X()) < 0;
		bool isTop = (y - obj->Y()) < 0;

		float dx, dy;

		Rect* player = (Rect*)BBox();
		Rect* enemy = (Rect*)obj->BBox();

		if (isTop)
			dy = enemy->Top() - player->Bottom();
		else
			dy = enemy->Bottom() - player->Top();

		if (isLeft)
			dx = enemy->Left() - player->Right();
		else
			dx = enemy->Right() - player->Left();

		if (abs(dy) < abs(dx) && isTop) {
			Level::score += 50;
			Level::scene->Delete(obj, MOVING);
			Level::audio->Play(2);
		}
		else {
			Level::isGameOver = true;
		}
	}
	else if (obj->Type() == ObjTypes::COLLECTABLE) {
		Level::score += 10;
		Level::scene->Delete(obj, STATIC);
		Level::audio->Play(1);
	}
	else if (obj->Type() == ObjTypes::FINISH) {
		Level::isFinished = true;
	}
}

void Player::Draw()
{
	anim->Draw(x, y, Layer::MIDDLE, scale, rotation);
}

void Player::applyForce(Vector* force)
{
	*forceAccum = *forceAccum + force;
}

void Player::zeroGravityForce()
{
	forceAccum->setXY(forceAccum->X(), 0);
	hasZeroGravity = true;
}

