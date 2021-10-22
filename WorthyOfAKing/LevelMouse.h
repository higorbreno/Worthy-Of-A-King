#include "Object.h"
#include "Sprite.h"
#include <vector>

#ifndef LEVELMOUSE_H
#define LEVELMOUSE_H

class LevelMouse : public Object {
private:
	static const uint MAX_BLOCKS;
	static const uint MAX_OBSTACLES;
	static const uint MAX_ENEMIES;
	static const uint MAX_COLLECTABLES;

	bool isColliding;
	std::vector<Sprite*> blocks;
	std::vector<Sprite*> obstacles;
	std::vector<Sprite*> enemies;
	std::vector<Sprite*> collectables;
	Sprite* playerTile;
	Sprite* finishTile;
	uint mode;
	bool playerOnScene;

	void snapToGrid();
	void clampBlockId();
	void clampObstaclesId();
	void clampEnemiesId();
	void clampCollectablesId();
	void clampMode();

public:
	static int blocksId;
	static int obstaclesId;
	static int enemiesId;
	static int collectablesId;

	LevelMouse();
	~LevelMouse();
	void Update();
	void Draw();
	void OnCollision(Object* obj);
};

#endif