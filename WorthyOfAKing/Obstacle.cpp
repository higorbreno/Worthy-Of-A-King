#include "Obstacle.h"
#include "Enums.h"

Obstacle::Obstacle(int id, float x, float y)
{
	type = ObjTypes::OBSTACLE;

	switch (id) {
	case 0:
		spr = new Sprite("Resources/SpikeDown.png");
		BBox(new Rect(-16.0f, 9.0f, 16.0f, 16.0f));
		break;
	case 1:
		spr = new Sprite("Resources/SpikeRight.png");
		BBox(new Rect(9.0f, -16.0f, 16.0f, 16.0f));
		break;
	case 2:
		spr = new Sprite("Resources/SpikeUp.png");
		BBox(new Rect(-16.0f, -16.0f, 16.0f, -9.0f));
		break;
	case 3:
		spr = new Sprite("Resources/SpikeLeft.png");
		BBox(new Rect(-16.0f, -16.0f, -9.0f, 16.0f));
		break;
	}
	
	MoveTo(x, y);
}

Obstacle::~Obstacle()
{
	delete spr;
}

void Obstacle::Update()
{
}

void Obstacle::Draw()
{
	spr->Draw(x, y);
}
