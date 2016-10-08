#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();
	~Enemy();

	virtual void init(ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);

protected:
	virtual void move(int deltaTime);
};

