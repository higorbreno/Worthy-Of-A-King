#include "Object.h"
#include "Sprite.h"

#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle : public Object {
private:
	int id;
	Sprite* spr;

public:
	Obstacle(int id, float x, float y);
	~Obstacle();
	void Update();
	void Draw();
};

#endif // !OBSTACLE_H
