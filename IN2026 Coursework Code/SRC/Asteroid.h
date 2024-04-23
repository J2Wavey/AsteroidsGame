#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "GameObject.h"

class Asteroid : public GameObject
{
public:
	Asteroid(void);
	~Asteroid(void);
	//static bool shouldSlowDown;
	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
	void SlowDown(float factor); // Factor less than 1 will slow down the asteroid
	//void Update(int j);
};

#endif
