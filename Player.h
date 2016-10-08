#pragma once

#include "Character.h"
#include "Inventory.h"
#include "Block.h"

class Player : public Character
{
private:
	bool damaged = false;
	const int damageBlinkFrequency = 300;
	const int invulnerabilityPeriod = 3000;
	int invulnerabilityTimer = invulnerabilityPeriod;

	Inventory inventory;

protected:
	virtual void move(int deltaTime);
	
public:
	Player();
	virtual ~Player();

	virtual void init(ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
	void takeDamage();
};

