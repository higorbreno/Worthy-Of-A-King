#include "Collectable.h"
#include "Enums.h"

Collectable::Collectable(int id, float x, float y)
{
	type = ObjTypes::COLLECTABLE;
	
	if (id == 0) {
		ts = new TileSet("Resources/CoinSpriteSheet.png", 1, 4);
		anim = new Animation(ts, 0.120f, true);
		BBox(new Circle(8.0f));
	}
	
	MoveTo(x, y);
}

Collectable::~Collectable()
{
	delete ts;
	delete anim;
}

void Collectable::Update()
{
	anim->NextFrame();
}

void Collectable::Draw()
{
	anim->Draw(x, y);
}
