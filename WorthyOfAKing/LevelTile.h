#include "Object.h"
#include "Sprite.h"
#include <vector>

#ifndef LEVELTILE_H
#define LEVELTILE_H

enum TileType { PLAYER, BLOCK, OBSTACLE, ENEMY, COLLECTABLE, FINISH, Count };

class LevelTile : public Object {
private:
	int id;
	Sprite* spr;

public:
	TileType tileType;
	static std::vector<Image*> blocks;
	static std::vector<Image*> obstacles;
	static std::vector<Image*> enemies;
	static std::vector<Image*> collectables;

	int Id();
	LevelTile(float, float, TileType, int id = 0);
	~LevelTile();
	void Update();
	void Draw();
};

inline int LevelTile::Id()
{
	return id;
}

#endif