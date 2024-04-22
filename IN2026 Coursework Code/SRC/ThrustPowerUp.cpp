#include "ThrustPowerUp.h"
#include "AnimationManager.h"
#include "GameWorld.h"
#include "Spaceship.h"

// Constructor
ThrustPowerUp::ThrustPowerUp() : GameObject("ThrustPowerUp"), mRadius(1.0f) {
    // SetBoundingShape(make_shared<BoundingSphere>(this, mRadius)); // Set in Asteroids class
    //SetSprite(AnimationManager::GetInstance().GetAnimationByName("thrustPowerUp"));
}

// Destructor
ThrustPowerUp::~ThrustPowerUp() {
}

// Update function
void ThrustPowerUp::Update(int dt) {
    GameObject::Update(dt);
}

// Render function
void ThrustPowerUp::Render() {
    if (mSprite.get() != NULL) {
        mSprite->Render();
    }
    GameObject::Render();
}

// Collision test
bool ThrustPowerUp::CollisionTest(shared_ptr<GameObject> o) {
    // Check if the 'other' object is a Spaceship or Bullet, not an Asteroid
    if (o->GetType() == GameObjectType("Asteroid")) return false; // Ignore collision with Asteroids
    if (o->GetType() != GameObjectType("Spaceship") && o->GetType() != GameObjectType("Bullet")) return false; // Only care about Spaceship and Bullet

    if (mBoundingShape.get() == nullptr) return false;
    if (o->GetBoundingShape().get() == nullptr) return false;

    return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

// Collision handling
void ThrustPowerUp::OnCollision(const GameObjectList& objects) {
    // Flag for removal if collided with the correct object type
    mWorld->FlagForRemoval(GetThisPtr());
}