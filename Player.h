#pragma once

#include "Character.h"
#include "Inventory.h"
#include "Block.h"

class Player : public Character
{

public:
	Player();
	virtual ~Player();

	virtual void init(ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
    virtual void render(ShaderProgram &program) override;

    Item *getSelectedItem() const;
    int getSelectedItemIndex() const;

	void takeDamage();

private:
    const int maxHealth = 10;
    int health = maxHealth;
    const int heartSize = 25;
    const glm::ivec2 heartLinePosition = glm::ivec2(450, 15);
    Texture textureHeart;
    Sprite *spriteHeart = NULL;

    bool damaged = false;
    const int damageBlinkFrequency = 300;
    const int invulnerabilityPeriod = 2000;
    int invulnerabilityTimer = invulnerabilityPeriod;

    Inventory inventory;
    Item *selectedItem = NULL;
    int selectedItemIndex = 0;

protected:
    virtual void move(int deltaTime);
    void handleItemSelection();
    void handleMouseActions();
    void renderHearts(ShaderProgram &program);
};

