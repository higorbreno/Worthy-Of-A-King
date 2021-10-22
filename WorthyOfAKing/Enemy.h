#include "Object.h"
#include "Animation.h"
#include "Vector.h"

#ifndef ENEMY_H
#define ENEMY_H

enum EnemyAnim{ RIGHT, LEFT };

class Enemy : public Object {
private:
	int id;
	float turnTime;
	int velx;
	TileSet* ts;
	Animation* anim;
	bool isGoingLeft;

	static Vector gravity;
	float mass;
	float inverseMass;
	Vector forceAccum;
	Vector velocity;

	void zeroGravityForce();
	void applyForce(Vector*);

public:
	Enemy(int id, float x, float y);
	~Enemy();
	void Update();
	void Draw();
	void OnCollision(Object* obj);
};

#endif