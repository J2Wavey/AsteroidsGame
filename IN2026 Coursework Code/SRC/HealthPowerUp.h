#pragma once
#ifndef HEALTH_POWER_UP_H
#define HEALTH_POWER_UP_H

#include "GameUtil.h"
#include "GameObject.h"
#include "BoundingSphere.h"

class HealthPowerUp : public GameObject {
public:
    HealthPowerUp();
    HealthPowerUp(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
    virtual ~HealthPowerUp();

    void Update(int t);
    void Render() override;

    bool CollisionTest(shared_ptr<GameObject> other) override;
    void OnCollision(const GameObjectList& objects) override;

    void SetSprite(shared_ptr<Sprite> sprite) { mSprite = sprite; }

private:
    shared_ptr<Sprite> mSprite;
    float mRadius;
};

#endif // HEALTH_POWER_UP_H