#include "LevelTile.h"

std::vector<Image*> LevelTile::blocks;
std::vector<Image*> LevelTile::obstacles;
std::vector<Image*> LevelTile::enemies;
std::vector<Image*> LevelTile::collectables;

LevelTile::LevelTile(float x, float y, TileType t, int id)
{
	if (blocks.empty()) {
		for (int i = 0; i < 70; ++i) {
			string idString = std::to_string(i);
			blocks.push_back(new Image("Resources/Blocks/" + idString + ".png"));
		}
	}
	if (obstacles.empty()) {
		for (int i = 0; i < 70; ++i) {
			string idString = std::to_string(i);
			obstacles.push_back(new Image("Resources/Obstacles/" + idString + ".png"));
		}
	}
	if (enemies.empty()) {
		for (int i = 0; i < 70; ++i) {
			string idString = std::to_string(i);
			enemies.push_back(new Image("Resources/Enemies/" + idString + ".png"));
		}
	}
	if (collectables.empty()) {
		for (int i = 0; i < 70; ++i) {
			string idString = std::to_string(i);
			collectables.push_back(new Image("Resources/Collectables/" + idString + ".png"));
		}
	}

	this->id = id;
	tileType = t;

	switch (t) {
	case TileType::PLAYER:
		spr = new Sprite("Resources/Player.png");
		BBox(new Rect(-48.0f, -48.0f, 48.0f, 48.0f));
		break;
	case TileType::FINISH:
		spr = new Sprite("Resources/Finish.png");
		BBox(new Rect(-16.0f, -48.0f, 16.0f, 48.0f));
		break;
	case TileType::BLOCK:
		spr = new Sprite(blocks[id]);
		if (id < 27 || id > 50)
			BBox(new Rect(-16.0f, -16.0f, 16.0f, 16.0f));
		else
			MoveTo(x, y, Layer::BACK);
		break;
	case TileType::OBSTACLE:
		spr = new Sprite(obstacles[id]);
		BBox(new Rect(-16.0f, -16.0f, 16.0f, 16.0f));
		break;
	case TileType::ENEMY:
		spr = new Sprite(enemies[id]);
		BBox(new Rect(-48.0f, -48.0f, 48.0f, 48.0f));
		break;
	case TileType::COLLECTABLE:
		spr = new Sprite(collectables[id]);
		BBox(new Rect(-16.0f, -16.0f, 16.0f, 16.0f));
		break;
	}
}

LevelTile::~LevelTile()
{
	delete spr;
}

void LevelTile::Update()
{
}

void LevelTile::Draw()
{
	spr->Draw(x, y);
}
