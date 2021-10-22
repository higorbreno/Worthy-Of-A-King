#include "Object.h"
#include "Sprite.h"

#ifndef FINISH_H
#define FINISH_H

class Finish : public Object {
private:
	Sprite* spr;

public:
	Finish(float x, float y);
	~Finish();
	void Update();
	void Draw();
};

#endif