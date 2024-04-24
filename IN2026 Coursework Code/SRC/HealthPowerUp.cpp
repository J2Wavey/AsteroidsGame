#include "HealthPowerUp.h"
#include "AnimationManager.h"
#include "GameWorld.h"
#include "Spaceship.h"

// this is the default constructor for the health power up class 
HealthPowerUp::HealthPowerUp() // initilaizes the power up as a type of game object and is setting a deafult radius for this boundshape 
    : GameObject("HealthPowerUp"), mRadius(1.0f) {
    //SetBoundingShape(make_shared<BoundingSphere>(this, mRadius));
}


// this is the destructor for the power up class 
HealthPowerUp::~HealthPowerUp() {
}

void HealthPowerUp::Update(int dt) {// this is the update method for the health power up 
    // Call parent update function
    GameObject::Update(dt);
}

void HealthPowerUp::Render() { // this is the render function, which is to draw the health power up
    if (mSprite.get() != NULL) {
        mSprite->Render();
    }

    GameObject::Render();// calling the base class render to hndle any further rendering 
}
// this is the collisontest function which ttests if this health power up has collidied with another object 
// this function will return true, if the there is collison between the health power, bullet or space ship 
bool HealthPowerUp::CollisionTest(shared_ptr<GameObject> o)
{
    // Check if the 'other' object is a Spaceship or Bullet, not an Asteroid
    if (o->GetType() == GameObjectType("Asteroid")) return false; // Ignore collision with Asteroids
    if (o->GetType() != GameObjectType("Spaceship") && o->GetType() != GameObjectType("Bullet")) return false; // Only care about Spaceship and Bullet

    if (mBoundingShape.get() == nullptr) return false;
    if (o->GetBoundingShape().get() == nullptr) return false;

    return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

// this is used when there is a collision. 
void HealthPowerUp::OnCollision(const GameObjectList& objects)
{
   // mWorld->FlagForRemoval(GetThisPtr());
}