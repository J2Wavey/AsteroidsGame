#include <stdlib.h>
#include "GameUtil.h"
#include "Asteroid.h"
#include "BoundingShape.h"

Asteroid::Asteroid(void) : GameObject("Asteroid")
{
	mAngle = rand() % 360;
	mRotation =  0;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity.x = -1.0 * cos(DEG2RAD*mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD*mAngle);
	mVelocity.z = 0.0;
	
}

Asteroid::~Asteroid(void)
{
}
//bool Asteroid::shouldSlowDown = false;
void Asteroid::SlowDown(float factor) {
	mVelocity.x *= factor;
	mVelocity.y *= factor;
	mRotation *= factor;
}
/*void Asteroid::Update(int j) {
	if (shouldSlowDown) {
		SlowDown(0.4f);
	}
}*/
bool Asteroid::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() == GameObjectType("Asteroid") || o->GetType() == GameObjectType("HealthPowerUp")) return false;
	if (o->GetType() != GameObjectType("Spaceship") && o->GetType() != GameObjectType("Bullet")) return false; // only care about Spaceship and Bullet in terms of detection of collisions
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Asteroid::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}
