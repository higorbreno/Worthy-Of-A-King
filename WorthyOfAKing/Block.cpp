#include "Block.h"
#include "Enums.h"

std::vector<Image*> Block::images;

Block::Block(int id, float posx, float posy)
{
	type = ObjTypes::BLOCK;

	if (images.empty()) {
		for (int i = 0; i < 70; ++i) {
			string idString = std::to_string(i);
			images.push_back(new Image("Resources/Blocks/" + idString + ".png"));
		}
	}
		
	spr = new Sprite(images[id]);

	float posz;

	if (id >= 0 && id <= 26) {
		BBox(new Rect(-16.0f, -16.0f, 16.0f, 16.0f));
		blockType = BlockType::SOLID;
		posz = Layer::MIDDLE;
	}
	else if (id >= 51 && id <= 53) {
		BBox(new Rect(-12.0f, -16.0f, 12.0f, 16.0f));
		blockType = BlockType::STAIR;
		posz = Layer::MIDDLE;
	}
	else if (id >= 55 && id <= 60) {
		BBox(new Rect(-13.0f, -14.0f, 13.0f, 14.0f));
		blockType = BlockType::SCENEOBJ;
		posz = Layer::MIDDLE;
	}
	else if (id >= 61 && id <= 66) {
		blockType = BlockType::NONE;
		posz = Layer::UPPER + 0.01f;
	}
	else {
		blockType = BlockType::NONE;
		posz = Layer::BACK;
	}

	MoveTo(posx, posy, posz);
}


void Block::Update()
{
}

void Block::Draw()
{
	spr->Draw(x, y, z, scale);
}

Block::~Block()
{
	delete spr;
}