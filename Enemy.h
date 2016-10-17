#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
    virtual void init(ShaderProgram &shaderProgram) = 0;
    virtual void update(int deltaTime) = 0;
    virtual void move(int deltaTime) = 0;

    virtual void hit();

protected:
    Enemy();
    virtual ~Enemy();
};

