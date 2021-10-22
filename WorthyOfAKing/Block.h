#include "Object.h"
#include "Sprite.h"
#include <vector>

#ifndef BLOCK_H
#define BLOCK_H

enum BlockType {
	SOLID, STAIR, SCENEOBJ, NONE
};

class Block : public Object {
private:
	int id;
	Sprite* spr;

public:
	BlockType blockType;
	static std::vector<Image*> images; 

	Block(int, float, float);
	void Update();
	void Draw();
	~Block();
};

#endif