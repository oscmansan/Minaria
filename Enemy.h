#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
    bool dead = false;
    float timeSinceDead = 0.0f;

    virtual void init();
    virtual void update(int deltaTime);
    virtual void move(int deltaTime);

    virtual void takeDamage(int damage = 1);

protected:
    Enemy();
    virtual ~Enemy();

    void beginToDie();
    void die();
};

