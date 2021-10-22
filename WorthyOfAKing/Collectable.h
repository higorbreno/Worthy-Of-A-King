#include "Object.h"
#include "Animation.h"

#ifndef COLLECTABLE_H
#define COLLECTABLE_H

class Collectable : public Object {
private:
	int id;
	TileSet* ts;
	Animation* anim;

public:
	Collectable(int id, float x, float y);
	~Collectable();
	void Update();
	void Draw();
};

#endif