#include "LevelMouse.h"
#include "LevelTile.h"
#include "LevelCreator.h"

int LevelMouse::blocksId = 0;
int LevelMouse::obstaclesId = 0;
int LevelMouse::enemiesId = 0;
int LevelMouse::collectablesId = 0;

const uint LevelMouse::MAX_BLOCKS = 70;
const uint LevelMouse::MAX_OBSTACLES = 4;
const uint LevelMouse::MAX_ENEMIES = 1;
const uint LevelMouse::MAX_COLLECTABLES = 1;

LevelMouse::LevelMouse()
{
	isColliding = false;
	mode = TileType::PLAYER;
	playerOnScene = false;

	if (blocks.empty()) {
		for (int i = 0; i < MAX_BLOCKS; ++i) {
			string idString = std::to_string(i);
			blocks.push_back(new Sprite("Resources/Blocks/" + idString + ".png"));
		}
	}
	if (obstacles.empty()) {
		for (int i = 0; i < MAX_OBSTACLES; ++i) {
			string idString = std::to_string(i);
			obstacles.push_back(new Sprite("Resources/Obstacles/" + idString + ".png"));
		}
	}
	if (enemies.empty()) {
		for (int i = 0; i < MAX_ENEMIES; ++i) {
			string idString = std::to_string(i);
			enemies.push_back(new Sprite("Resources/Enemies/" + idString + ".png"));
		}
	}
	if (collectables.empty()) {
		for (int i = 0; i < MAX_COLLECTABLES; ++i) {
			string idString = std::to_string(i);
			collectables.push_back(new Sprite("Resources/Collectables/" + idString + ".png"));
		}
	}
	playerTile = new Sprite("Resources/Player.png");
	finishTile = new Sprite("Resources/Finish.png");

	BBox(new Point());
}

LevelMouse::~LevelMouse()
{
	if (!blocks.empty()) {
		for (auto block : blocks)
			delete block;
		blocks.clear();
	}
	if (!obstacles.empty()) {
		for (auto obstacle : obstacles)
			delete obstacle;
		obstacles.clear();
	}
	if (!enemies.empty()) {
		for (auto enemy : enemies)
			delete enemy;
		enemies.clear();
	}
	if (!collectables.empty()) {
		for (auto collectable : collectables)
			delete collectable;
		collectables.clear();
	}
	delete playerTile;
	delete finishTile;
}

void LevelMouse::Update()
{
	MoveTo(window->MouseX(), window->MouseY());
	snapToGrid();

	int* id = &blocksId;

	switch (mode) {
	case TileType::BLOCK:
		id = &blocksId;
		break;
	case TileType::OBSTACLE:
		id = &obstaclesId;
		break;
	case TileType::ENEMY:
		id = &enemiesId;
		break;
	case TileType::COLLECTABLE:
		id = &collectablesId;
		break;
	}

	if (mode != TileType::PLAYER) {
		if (window->KeyPress(VK_LEFT))
			--*id;
		if (window->KeyPress(VK_DOWN))
			*id -= 10;
		if (window->KeyPress(VK_RIGHT))
			++*id;
		if (window->KeyPress(VK_UP))
			*id += 10;
	}

	clampBlockId();
	clampCollectablesId();
	clampEnemiesId();
	clampObstaclesId();

	if (window->KeyPress('M'))
		mode = TileType(mode + 1);

	clampMode();

	if (window->KeyDown(VK_LBUTTON) && (!isColliding || (mode == TileType::BLOCK && blocksId >= 27 && blocksId <= 50))) {
		if (mode == TileType::PLAYER && !playerOnScene) {
			playerOnScene = true;
			LevelTile* tile = new LevelTile(x, y, TileType(mode));
			tile->MoveTo(x, y);
			LevelCreator::scene->Add(tile, STATIC);
			LevelCreator::tiles.push_back(tile);
		}
		else if (mode == TileType::FINISH) {
			LevelTile* tile = new LevelTile(x, y, TileType(mode));
			tile->MoveTo(x, y);
			LevelCreator::scene->Add(tile, STATIC);
			LevelCreator::tiles.push_back(tile);
		}
		else if (mode == TileType::BLOCK) {
			LevelTile* tile = new LevelTile(x, y, TileType(mode), blocksId);
			tile->MoveTo(x, y);
			LevelCreator::scene->Add(tile, STATIC);
			LevelCreator::tiles.push_back(tile);
		}
		else if (mode == TileType::OBSTACLE) {
			LevelTile* tile = new LevelTile(x, y, TileType(mode), obstaclesId);
			tile->MoveTo(x, y);
			LevelCreator::scene->Add(tile, STATIC);
			LevelCreator::tiles.push_back(tile);
		}
		else if (mode == TileType::ENEMY) {
			LevelTile* tile = new LevelTile(x, y, TileType(mode), enemiesId);
			tile->MoveTo(x, y);
			LevelCreator::scene->Add(tile, STATIC);
			LevelCreator::tiles.push_back(tile);
		}
		else if (mode == TileType::COLLECTABLE) {
			LevelTile* tile = new LevelTile(x, y, TileType(mode), collectablesId);
			tile->MoveTo(x, y);
			LevelCreator::scene->Add(tile, STATIC);
			LevelCreator::tiles.push_back(tile);
		}
	}
	isColliding = false;
}

void LevelMouse::Draw()
{
	if (mode == TileType::PLAYER)
		playerTile->Draw(x, y, z, scale, rotation, { 1,1,1,0.6f });
	else if (mode == TileType::FINISH)
		finishTile->Draw(x, y, z, scale, rotation, { 1,1,1,0.6f });
	else if (mode == TileType::BLOCK)
		blocks[blocksId]->Draw(x, y, z, scale, rotation, { 1,1,1,0.6f });
	else if (mode == TileType::OBSTACLE)
		obstacles[obstaclesId]->Draw(x, y, z, scale, rotation, { 1,1,1,0.6f });
	else if (mode == TileType::ENEMY)
		enemies[enemiesId]->Draw(x, y, z, scale, rotation, { 1,1,1,0.6f });
	else if (mode == TileType::COLLECTABLE)
		collectables[collectablesId]->Draw(x, y, z, scale, rotation, { 1,1,1,0.6f });
}

void LevelMouse::OnCollision(Object* obj)
{
	isColliding = true;
	if (window->KeyDown(VK_RBUTTON)) {
		LevelTile* tile = (LevelTile*)obj;
		if (tile->tileType == TileType::PLAYER)
			playerOnScene = false;
		LevelCreator::tiles.remove(tile);
		LevelCreator::scene->Delete(obj, STATIC);
	}
	else if (window->KeyPress(VK_MBUTTON)) {
		LevelTile* tile = (LevelTile*)obj;
		switch (tile->tileType) {
		case TileType::BLOCK:
			blocksId = tile->Id();
			mode = TileType::BLOCK;
			break;
		case TileType::OBSTACLE:
			obstaclesId = tile->Id();
			mode = TileType::OBSTACLE;
			break;
		case TileType::ENEMY:
			enemiesId = tile->Id();
			mode = TileType::ENEMY;
			break;
		case TileType::COLLECTABLE:
			collectablesId = tile->Id();
			mode = TileType::COLLECTABLE;
			break;
		}
	}
}

void LevelMouse::snapToGrid()
{
	int posx = ((int(x + Game::camera->X()) / 32) * 32) + 16;
	int posy = ((int(y + Game::camera->Y()) / 32) * 32) + 16;
	MoveTo(posx, posy);
}

void LevelMouse::clampBlockId()
{
	while (blocksId < 0)
		blocksId += MAX_BLOCKS;
	while (blocksId >= MAX_BLOCKS)
		blocksId -= MAX_BLOCKS;
}

void LevelMouse::clampObstaclesId()
{
	while (obstaclesId < 0)
		obstaclesId += MAX_OBSTACLES;
	while (obstaclesId >= MAX_OBSTACLES)
		obstaclesId -= MAX_OBSTACLES;
}

void LevelMouse::clampEnemiesId()
{
	while (enemiesId < 0)
		enemiesId += MAX_ENEMIES;
	while (enemiesId >= MAX_ENEMIES)
		enemiesId -= MAX_ENEMIES;
}

void LevelMouse::clampCollectablesId()
{
	while (collectablesId < 0)
		collectablesId += MAX_COLLECTABLES;
	while (collectablesId >= MAX_COLLECTABLES)
		collectablesId -= MAX_COLLECTABLES;
}

void LevelMouse::clampMode()
{
	while (mode < TileType::PLAYER)
		mode = TileType(mode + TileType::Count);
	while (mode >= TileType::Count)
		mode = TileType(mode - TileType::Count);
}
