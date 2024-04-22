#include "HealthPowerUp.h"
#include "AnimationManager.h"
#include "GameWorld.h"
#include "Spaceship.h"

// Default constructor
HealthPowerUp::HealthPowerUp()
    : GameObject("HealthPowerUp"), mRadius(1.0f) {
    //SetBoundingShape(make_shared<BoundingSphere>(this, mRadius));
}


// Destructor
HealthPowerUp::~HealthPowerUp() {
}

void HealthPowerUp::Update(int dt) {
    // Call parent update function
    GameObject::Update(dt);
}

void HealthPowerUp::Render() {
    if (mSprite.get() != NULL) {
        mSprite->Render();
    }

    GameObject::Render();
}

bool HealthPowerUp::CollisionTest(shared_ptr<GameObject> o)
{

    // Check if the 'other' object is a Spaceship or Bullet, not an Asteroid
    if (o->GetType() == GameObjectType("Asteroid")) return false; // Ignore collision with Asteroids
    if (o->GetType() != GameObjectType("Spaceship") && o->GetType() != GameObjectType("Bullet")) return false; // Only care about Spaceship and Bullet

    if (mBoundingShape.get() == nullptr) return false;
    if (o->GetBoundingShape().get() == nullptr) return false;

    return mBoundingShape->CollisionTest(o->GetBoundingShape());
}


void HealthPowerUp::OnCollision(const GameObjectList& objects)
{
   // mWorld->FlagForRemoval(GetThisPtr());
}