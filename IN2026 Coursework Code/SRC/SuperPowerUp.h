#pragma once
#pragma once
#pragma once
#ifndef SUPER_POWER_UP_H
#define SUPER_POWER_UP_H

#include "GameUtil.h"
#include "GameObject.h"
#include "BoundingSphere.h"

class SuperPowerUp : public GameObject {
public:
    SuperPowerUp();
    virtual ~SuperPowerUp();

    void Update(int t) override;
    void Render() override;

    bool CollisionTest(shared_ptr<GameObject> other) override;
    void OnCollision(const GameObjectList& objects) override;

    void SetSprite(shared_ptr<Sprite> sprite) { mSprite = sprite; }

private:
    shared_ptr<Sprite> mSprite;
    float mRadius;
  
};

#endif 
