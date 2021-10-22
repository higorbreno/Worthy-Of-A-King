#include "Enemy.h"
#include "Enums.h"
#include "Level.h"

Vector Enemy::gravity;

void Enemy::zeroGravityForce()
{
	forceAccum.setXY(forceAccum.X(), 0);
}

void Enemy::applyForce(Vector* force)
{
	forceAccum = forceAccum + force;
}

Enemy::Enemy(int id, float x, float y)
{
	gravity.setXY(0, 9.81f);
	type = ObjTypes::ENEMY;
	mass = 100;
	inverseMass = 1 / mass;
	turnTime = 0.0f;
	velx = -70;
	isGoingLeft = true;

	if (id == 0) {
		ts = new TileSet("Resources/SnakeSpriteSheet.png", 2, 4);
		anim = new Animation(ts, 0.120f, true);
		uint seqRight[4] = { 0,1,2,3 };
		uint seqLeft[4] = { 7,6,5,4 };
		anim->Add(RIGHT, seqRight, 4);
		anim->Add(LEFT, seqLeft, 4);
		BBox(new Rect(-18.0f, 4.0f, 18.0f, 32.0f));
	}

	MoveTo(x, y);
}

Enemy::~Enemy()
{
	delete ts;
	delete anim;
}

void Enemy::Update()
{
	applyForce(&gravity);
	velocity = forceAccum * inverseMass;
	Translate(velocity.X() * 100 * gameTime, velocity.Y() * 100 * gameTime);

	turnTime += gameTime;

	if (turnTime >= 1.0f) {
		turnTime = 0.0f;
		velx *= -1;
		isGoingLeft = !isGoingLeft;
	}


	Translate(velx * gameTime, 0);

	if (isGoingLeft)
		anim->Select(LEFT);
	else 
		anim->Select(RIGHT);

	anim->NextFrame();
}

void Enemy::Draw()
{
	anim->Draw(x, y);
}

void Enemy::OnCollision(Object* obj)
{
	if (obj->Type() == ObjTypes::BLOCK) {
		bool isLeft = (x - obj->X()) < 0;
		bool isTop = (y - obj->Y()) < 0;

		float dx, dy;

		Rect* enemy = (Rect*)BBox();
		Rect* block = (Rect*)obj->BBox();

		if (isTop)
			dy = block->Top() - enemy->Bottom();
		else
			dy = block->Bottom() - enemy->Top();

		if (isLeft)
			dx = block->Left() - enemy->Right();
		else
			dx = block->Right() - enemy->Left();

		if (abs(dx) <= abs(dy)) {
			Translate(dx, 0);
		}
		else {
			Translate(0, dy);
			if(isTop)
				zeroGravityForce();
		}
	}
}
