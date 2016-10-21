#include "Player.h"
#include "Game.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Bomb.h"
#include "Block.h"
#include "TileMap.h"
#include "ItemBomb.h"
#include "SceneGame.h"
#include "ItemSword.h"
#include "ItemPickaxe.h"

Player::Player() {}

Player::~Player()
{
    delete spriteHeart;
}


void Player::init()
{
    Character::init();

    ShaderProgram *program = Game::getCurrentScene()->getShaderProgram();

    // Heart
    textureHeart.loadFromFile("images/heartSpritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    textureHeart.setMinFilter(GL_NEAREST);
    textureHeart.setWrapS(GL_CLAMP_TO_EDGE);
    spriteHeart = Sprite::createSprite(glm::ivec2(heartSize), glm::vec2(0.29f, 1.0f), &textureHeart, program);
    spriteHeart->setNumberAnimations(3);
    spriteHeart->addKeyframe(0, glm::vec2(0.7f, 0.f));
    spriteHeart->addKeyframe(1, glm::vec2(0.35f, 0.f));
    spriteHeart->addKeyframe(2, glm::vec2(0.0f, 0.f));
    //

    // Player
    spritesheet.loadFromFile("images/miner.png", TEXTURE_PIXEL_FORMAT_RGBA);

    float dx = 1.0f / 10, dy = 1.0f / 4;
    sprite = Sprite::createSprite(glm::ivec2(36, 48), glm::vec2(0.075f, 0.25f), &spritesheet, program);
    sprite->setNumberAnimations(DEAD+1);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
    sprite->addKeyframe(STAND_LEFT, glm::vec2(dx * 0, dy * 0));
    sprite->setAnimationSpeed(STAND_RIGHT, 8);
    sprite->addKeyframe(STAND_RIGHT, glm::vec2(dx * 0, dy * 1));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(dx * 0, dy * 0));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(dx * 1, dy * 0));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(dx * 2, dy * 0));
	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(dx * 0, dy * 1));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(dx * 1, dy * 1));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(dx * 2, dy * 1));

    /*
        PICKAXE_LEFT, PICKAXE_RIGHT,
        SWORD_LEFT, SWORD_RIGHT,
        BOMB_LEFT, BOMB_RIGHT,
        DEAD
        */
    sprite->setAnimationSpeed(PICKAXE_LEFT, 8);
    sprite->addKeyframe(PICKAXE_LEFT, glm::vec2(dx * 3, dy * 0));
    sprite->addKeyframe(PICKAXE_LEFT, glm::vec2(dx * 4, dy * 0));
    sprite->addKeyframe(PICKAXE_LEFT, glm::vec2(dx * 5, dy * 0));
    sprite->setAnimationSpeed(PICKAXE_RIGHT, 8);
    sprite->addKeyframe(PICKAXE_RIGHT, glm::vec2(dx * 3, dy * 1));
    sprite->addKeyframe(PICKAXE_RIGHT, glm::vec2(dx * 4, dy * 1));
    sprite->addKeyframe(PICKAXE_RIGHT, glm::vec2(dx * 5, dy * 1));

    sprite->setAnimationSpeed(SWORD_LEFT, 8);
    sprite->addKeyframe(SWORD_LEFT, glm::vec2(dx * 7, dy * 2));
    sprite->addKeyframe(SWORD_LEFT, glm::vec2(dx * 8, dy * 2));
    sprite->addKeyframe(SWORD_LEFT, glm::vec2(dx * 9, dy * 2));
    sprite->setAnimationSpeed(SWORD_RIGHT, 8);
    sprite->addKeyframe(SWORD_RIGHT, glm::vec2(dx * 7, dy * 2));
    sprite->addKeyframe(SWORD_RIGHT, glm::vec2(dx * 8, dy * 2));
    sprite->addKeyframe(SWORD_RIGHT, glm::vec2(dx * 9, dy * 2));
    //

    inventory.init();

    setPosition(glm::ivec2(700, 1200));

    for (int i = 0; i < 99; ++i) inventory.addItem<ItemBomb>();
}

void Player::update(int deltaTime)
{
    Character::update(deltaTime);

    if (!dead)
    {
        if (damaged)
        {
            sprite->setVisible(Scene::getCurrentTime() % (damageBlinkFrequency * 2) < damageBlinkFrequency);
            invulnerabilityTimer -= deltaTime;
        }

        if (invulnerabilityTimer <= 0) {
            damaged = false;
            sprite->setVisible(true);
            invulnerabilityTimer = invulnerabilityPeriod;
        }

        handleItemSelection();
        handleMouseActions();
    }
    else
    {
        rotation += 0.5f;
        timeSinceDead += deltaTime;
        if (timeSinceDead > 2000)
        {
            die();
        }
    }
}

void Player::render(ShaderProgram &program)
{
    Character::render(program);
    renderHearts(program);
}

Item *Player::getSelectedItem() const
{
    return selectedItem;
}

int Player::getSelectedItemIndex() const
{
    return selectedItemIndex;
}

Inventory *Player::getInventory()
{
    return &inventory;
}

void Player::move(int deltaTime)
{
	bool leftPressed = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
	bool rightPressed = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
	bool bothPressed = leftPressed && rightPressed;
	bool anyPressed = leftPressed || rightPressed;

	if (bothPressed || (velocity.x == 0 && !anyPressed))
	{
        if (!usingItem)
        {
            if (sprite->animation() == MOVE_LEFT)
                sprite->changeAnimation(STAND_LEFT);
            else if (sprite->animation() == MOVE_RIGHT)
                sprite->changeAnimation(STAND_RIGHT);
        }
		velocity.x = 0;
	}
	else
	{
		if(leftPressed)
		{
            if (!usingItem)
            {
                if (sprite->animation() != MOVE_LEFT)
                    sprite->changeAnimation(MOVE_LEFT);
            }
            velocity.x = -8;
		}

		if (rightPressed)
		{
            if (!usingItem)
            {
                if (sprite->animation() != MOVE_RIGHT)
                    sprite->changeAnimation(MOVE_RIGHT);
            }
            velocity.x = 8;
		}
	}

	if (!anyPressed)
	{
		velocity.x = 0;
	}
	
	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !bJumping)
	{
		jump();
	}

    Character::applyGravity();
}

void Player::handleItemSelection()
{
    for (int i = 0; i < inventory.getNumSlots(); ++i)
    {
        // Key selection
        if (Game::instance().getKey( char('1' + i) ))
        {
            selectedItemIndex = i;
            break;
        }
        else if (Game::instance().getMouseLeftButtonDown())  // Mouse selection
        {
            glm::ivec2 mousePosScreen = Game::instance().getMousePosScreen();
            Rect slotRect = inventory.getSlotScreenRect(i);
            if (slotRect.contains(mousePosScreen))
            {
                selectedItemIndex = i;
                break;
            }
        }
    }

    // Q & E selection
    if (Game::instance().getKeyDown('q')) { --selectedItemIndex; }
    if (Game::instance().getKeyDown('e')) { ++selectedItemIndex; }

    // Limit itemIndex and update selectedItem
    selectedItemIndex = min(selectedItemIndex, inventory.getNumSlots()-1);
    selectedItemIndex = max(selectedItemIndex, 0);
    selectedItem = inventory.getItem(selectedItemIndex);
}

void Player::handleMouseActions()
{
    TileMap *tmap = Game::getCurrentSceneGame()->getTileMap();
    glm::ivec2 mousePos = Game::instance().getMousePosWorld();

    if (!Game::instance().getMouseLeftButton())
        usingItem = false;

    Block *mouseBlock = tmap->getBlock(mousePos);
    if (mouseBlock != lastMouseBlock)
    {
        if (lastMouseBlock)
        {
            lastMouseBlock->onHitEnd();
            lastMouseBlock = NULL;
        }
    }
    if (!Game::instance().getMouseRightButton())
    {
        if (lastMouseBlock)
        {
            lastMouseBlock->onHitEnd();
        }
    }
    lastMouseBlock = mouseBlock;

    if (!selectedItem || !dynamic_cast<ItemPickaxe*>(selectedItem)) { lastMouseBlock = NULL; }
    if (selectedItem)
    {
        if (dynamic_cast<ItemPickaxe*>(selectedItem))
        {
            if (Game::instance().getMouseLeftButtonDown())
            {
                usingItem = true;
                sprite->changeAnimation(lookingLeft() ? PICKAXE_LEFT : PICKAXE_RIGHT);
            }

            if (Game::instance().getMouseLeftButton())
            {
                // BLOCK REMOVAL
                if (mouseBlock && mouseBlock->getType() != 0)
                {
                    mouseBlock->onHitBegin();
                }
            }
        }
        else if (dynamic_cast<ItemSword*>(selectedItem))
        {
            if (Game::instance().getMouseLeftButtonDown())
            {
                usingItem = true;
                sprite->changeAnimation(lookingLeft() ? SWORD_LEFT : SWORD_RIGHT);
            }

            if (Game::instance().getMouseLeftButton())
            {
                for (Character *c : Game::getCurrentSceneGame()->getCharacters())
                {
                    if (!c) continue;

                    Enemy *e = dynamic_cast<Enemy*>(c);
                    if (e)
                    {
                        if (e->getBoundingBox().contains(mousePos))
                        {
                            e->takeDamage();
                        }
                    }
                }
            }
        }
        else if (dynamic_cast<Block*>(selectedItem))
        {
            if (Game::instance().getMouseLeftButton())
            {
                if (tmap->getBlock(mousePos) == NULL) // Can it put a block where the mouse is?
                {
                    Block *b = dynamic_cast<Block*>(selectedItem);
                    // BLOCK ADDING
                    int amount = b->getAmount();
                    if (amount > 0)
                    {
                        Tile *addedBlock = NULL;
                        if (b->getType() == Block::DIRT)         { addedBlock = tmap->addTile<BlockDirt>(mousePos); }
                        else if (b->getType() == Block::ROCK)    { addedBlock = tmap->addTile<BlockRock>(mousePos); }
                        else if (b->getType() == Block::BEDROCK) { addedBlock = tmap->addTile<BlockBedRock>(mousePos); }
                        else if (b->getType() == Block::WOOD)    { addedBlock = tmap->addTile<BlockWood>(mousePos); }

                        if (addedBlock)
                        {
                            inventory.dropItem(selectedItemIndex);
                        }
                    }
                }
            }
        }
        else if (dynamic_cast<ItemBomb*>(selectedItem))
        {
            if (Game::instance().getMouseLeftButtonDown())
            {
                usingItem = true;

                Bomb *b = new Bomb();
                b->setPosition( getPosition() );

                glm::vec2 dir = glm::normalize( glm::vec2(mousePos - getPosition()) );
                float bombSpeed = 0.2f * glm::min(50.0f, glm::length(glm::vec2(mousePos - getPosition())));
                b->setVelocity( dir * bombSpeed );

                inventory.dropItem(selectedItemIndex);
            }
        }
    }
}

void Player::renderHearts(ShaderProgram &program)
{
    int heartMarginX = 10;
    for (int i = 0; i < maxHealth/2; ++i)
    {
        glm::ivec2 heartPos = heartLinePosition + (heartSize + heartMarginX) * glm::ivec2(i, 0);
        prepareModelViewMatrix(heartPos);
        program.setUniformMatrix4f("view", glm::mat4(1.0f));
        if ((i+1)*2 <= health)
        {
            spriteHeart->changeAnimation(2); // FULL HEART
        }
        else
        {
            if (i*2 + 1 == health) spriteHeart->changeAnimation(1); // MID HEART
            else spriteHeart->changeAnimation(0); // EMPTY HEART
        }
        spriteHeart->render();
    }
}

void Player::takeDamage(int damage)
{
    if (!damaged)
    {
        damaged = true;
        health -= damage;
        if (health < 0)
        {
            beginToDie();
        }
    }
}

void Player::beginToDie()
{
    dead = true;
}

void Player::die()
{
    Game::instance().gotoSceneGame();
}

void Player::onBlockDeleted(Block *b)
{
    if (lastMouseBlock == b)
    {
        lastMouseBlock = NULL;
    }
}
