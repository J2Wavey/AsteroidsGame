#include "SuperPowerUp.h"

SuperPowerUp::SuperPowerUp() : GameObject("SuperPowerUp"), mRadius(1.0f)
{


}
// destructor
SuperPowerUp::~SuperPowerUp() {

}

void SuperPowerUp::Update(int dt) {
    GameObject::Update(dt);
}

void SuperPowerUp::Render() {
    if (mSprite.get() != NULL) {
        mSprite->Render();
    }

    GameObject::Render();
}

bool SuperPowerUp::CollisionTest(shared_ptr<GameObject> o) {
    // Check if the 'other' object is a Spaceship or Bullet, not an Asteroid
    if (o->GetType() == GameObjectType("Asteroid")) return false; // Ignore collision with Asteroids
    if (o->GetType() != GameObjectType("Spaceship") && o->GetType() != GameObjectType("Bullet")) return false; // Only care about Spaceship and Bullet

    if (mBoundingShape.get() == nullptr) return false;
    if (o->GetBoundingShape().get() == nullptr) return false;

    return mBoundingShape->CollisionTest(o->GetBoundingShape());
}
void SuperPowerUp::OnCollision(const GameObjectList& objects) {

    mWorld->FlagForRemoval(GetThisPtr()); // Remove the power-up itself
}
