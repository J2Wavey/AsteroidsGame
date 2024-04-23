#include "DestroyAllPowerUp.h"
#include "AnimationManager.h"
#include "GameWorld.h"
#include "Spaceship.h"

// Default constructor
DestroyAllPowerUp::DestroyAllPowerUp() : GameObject("DestroyAllPowerUp"), mRadius(1.0f) {
   // SetBoundingShape(make_shared<BoundingSphere>(this, mRadius));
  //  SetSprite(AnimationManager::GetInstance().GetAnimationByName("destroy_all"));
}

// Destructor
DestroyAllPowerUp::~DestroyAllPowerUp() {
}

void DestroyAllPowerUp::Update(int dt) {
    GameObject::Update(dt);
}

void DestroyAllPowerUp::Render() {
    if (mSprite.get() != NULL) {
        mSprite->Render();
    }

    GameObject::Render();
}

bool DestroyAllPowerUp::CollisionTest(shared_ptr<GameObject> o) {
    // Only collide with a Spaceship
    if (o->GetType() != GameObjectType("Spaceship")) return false;

    if (mBoundingShape.get() == nullptr) return false;
    if (o->GetBoundingShape().get() == nullptr) return false;

    return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void DestroyAllPowerUp::OnCollision(const GameObjectList& objects) {
   
    mWorld->FlagForRemoval(GetThisPtr()); // Remove the power-up itself
}
