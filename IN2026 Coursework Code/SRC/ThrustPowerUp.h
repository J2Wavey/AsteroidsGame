#pragma once
#ifndef THRUST_POWER_UP_H
#define THRUST_POWER_UP_H

#include "GameUtil.h"
#include "GameObject.h"
#include "BoundingSphere.h"

class ThrustPowerUp : public GameObject {
public:
    ThrustPowerUp();
    virtual ~ThrustPowerUp();

    void Update(int t);
    void Render() override;

    bool CollisionTest(shared_ptr<GameObject> other) override;
    void OnCollision(const GameObjectList& objects) override;

    void SetSprite(shared_ptr<Sprite> sprite) { mSprite = sprite; }

private:
    shared_ptr<Sprite> mSprite;
    float mRadius; // This might be used to set the size of the bounding sphere
};

#endif // THRUST_POWER_UP_H