#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
    enum EnemyAnims
    {
        STAND_RIGHT = 0,
        STAND_LEFT,
        MOVE_LEFT,
        MOVE_RIGHT,
        DEAD
    };

    bool dead = false;
    float timeSinceDead = 0.0f;

    virtual void init();
    virtual void update(int deltaTime);
    virtual void move(int deltaTime);

    virtual Rect getBoundingBox() const override;

    virtual void takeDamage(int damage = 1);

protected:
    Enemy();
    virtual ~Enemy();

    void beginToDie();
    void die();
};

