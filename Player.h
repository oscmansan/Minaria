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
    Item *selectedItem = nullptr;
    int selectedItemIndex = 0;

protected:
	virtual void move(int deltaTime);
    void handleItemSelection();
    void handleMouseActions();

public:
	Player();
	virtual ~Player();

	virtual void init(ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
    virtual void render(ShaderProgram &program) override;

    Item *getSelectedItem() const;
    int getSelectedItemIndex() const;

	void takeDamage();
};

