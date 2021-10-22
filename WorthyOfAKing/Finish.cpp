#include "Finish.h"
#include "Enums.h"

Finish::Finish(float x, float y)
{
	type = ObjTypes::FINISH;

	spr = new Sprite("Resources/Finish.png");
	BBox(new Rect(-16.0, -48.0f, 16.0f, 48.0f));

	MoveTo(x, y);
}

Finish::~Finish()
{
	delete spr;
}

void Finish::Update()
{
}

void Finish::Draw()
{
	spr->Draw(x, y);
}
