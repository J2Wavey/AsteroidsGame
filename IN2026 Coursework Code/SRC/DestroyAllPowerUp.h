#pragma once
#pragma once
#ifndef DESTROY_ALL_POWER_UP_H
#define DESTROY_ALL_POWER_UP_H

#include "GameUtil.h"
#include "GameObject.h"
#include "BoundingSphere.h"

class DestroyAllPowerUp : public GameObject {
public:
    DestroyAllPowerUp();
    virtual ~DestroyAllPowerUp();

    void Update(int t) override;
    void Render() override;

    bool CollisionTest(shared_ptr<GameObject> other) override;
    void OnCollision(const GameObjectList& objects) override;

    void SetSprite(shared_ptr<Sprite> sprite) { mSprite = sprite; }

private:
    shared_ptr<Sprite> mSprite;
    float mRadius;
};

#endif // DESTROY_ALL_POWER_UP_H
