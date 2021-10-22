#include "Object.h"
#include "Animation.h"
#include "Vector.h"

#ifndef PLAYER_H
#define PLAYER_H

enum PlayerAnim {
	IDLE, IDLELEFT,
	WALK, WALKLEFT,
	JUMP, JUMPLEFT,
	HIT, HITLEFT,
	SLASH, SLASHLEFT,
	PUNCH, PUNCHLEFT,
	RUN, RUNLEFT,
	CLIMB, CLIMBLEFT
};

class Player : public Object {
private:
	static const double PIXEL_PER_METER;
	static Vector gravity;
	static Vector jumpForce;

	bool isClimbing;
	bool hasZeroGravity;
	bool isMovingLeft;
	uint state;

	float velx;
	float mass;
	float inverseMass;
	Vector* forceAccum;
	Vector* velocity;

	Animation* anim;

	void zeroGravityForce();

public:
	static TileSet* tileSet;
	
	Player();
	~Player();
	void Update();
	void OnCollision(Object* obj);
	void Draw();
	void applyForce(Vector*);
};

#endif