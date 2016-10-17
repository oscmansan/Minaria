#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();
	~Enemy();

    enum State {
        PATROL = 0,
        CHASE  = 1,
        ATTACK = 2
    };

	virtual void init(ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);

    void hit();

protected:
    State state;

	virtual void move(int deltaTime);
};

