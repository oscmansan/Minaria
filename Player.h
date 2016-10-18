#pragma once

#include "Block.h"
#include "Character.h"
#include "Inventory.h"

class Player : public Character
{

public:
	Player();
	virtual ~Player();

    virtual void init() override;
    virtual void update(int deltaTime) override;
    virtual void render(ShaderProgram &program) override;

    Item *getSelectedItem() const;
    int getSelectedItemIndex() const;

    Inventory *getInventory();

	void takeDamage();
    void onBlockDeleted(Block *b);

    Block *lastMouseBlock = NULL;

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

