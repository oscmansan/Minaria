#pragma once

#include "Block.h"
#include "Character.h"
#include "Inventory.h"

class Player : public Character
{

public:
    enum PlayerAnims
    {
        STAND_RIGHT = 0, STAND_LEFT,
        MOVE_LEFT, MOVE_RIGHT,
        PICKAXE_LEFT, PICKAXE_RIGHT,
        SWORD_LEFT, SWORD_RIGHT,
        BOMB_LEFT, BOMB_RIGHT,
        DEAD
    };

	Player();
	virtual ~Player();

    bool lookingLeft() const;
    virtual void init() override;
    virtual void update(int deltaTime) override;
    virtual void render(ShaderProgram &program) override;

    Item *getSelectedItem() const;
    int getSelectedItemIndex() const;

    Inventory *getInventory();

    void takeDamage(int damage = 1);
    void beginToDie();
    void die();
    void onBlockDeleted(Block *b);
    void renderHearts(ShaderProgram &program);
    bool isBlockSelected(Block *b);
    void winGame();

    Block *lastMouseBlock = NULL;

private:
    int itemCooldown = 300;
    int timeSinceLastItemUsed = 0;

    int swordRange = 64;

    bool usingItem = false;
    bool dead = false;
    float timeToDie = 4000.0f;
    float timeSinceDead = 0.0f;

    const int maxHealth = 10;
    int health = 1;//maxHealth;
    const int heartSize = 25;
    const glm::ivec2 heartLinePosition = glm::ivec2(450, 30);
    Texture textureHeart;
    Sprite *spriteHeart = NULL;

    bool damaged = false;
    const int damageBlinkFrequency = 300;
    const int invulnerabilityPeriod = 2000;
    int invulnerabilityTimer = invulnerabilityPeriod;

    Inventory *inventory = NULL;
    Item *selectedItem = NULL;
    int selectedItemIndex = 0;

    void updateMovementAnimation();

protected:
    virtual void move(int deltaTime);
    void handleItemSelection();
    void handleMouseActions();

    friend class ISceneNode;
};

