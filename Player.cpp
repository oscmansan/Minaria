#include "Player.h"
#include "Game.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Block.h"

Player::Player() {}

Player::~Player()
{
    delete spriteHeart;
}


void Player::init(ShaderProgram &shaderProgram)
{
	Character::init(shaderProgram);

    // Heart
    textureHeart.loadFromFile("images/heartSpritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    textureHeart.setMinFilter(GL_NEAREST);
    textureHeart.setWrapS(GL_CLAMP_TO_EDGE);
    spriteHeart = Sprite::createSprite(glm::ivec2(heartSize), glm::vec2(0.29f, 1.0f), &textureHeart, &shaderProgram);
    spriteHeart->setNumberAnimations(3);
    spriteHeart->addKeyframe(0, glm::vec2(0.7f, 0.f));
    spriteHeart->addKeyframe(1, glm::vec2(0.35f, 0.f));
    spriteHeart->addKeyframe(2, glm::vec2(0.0f, 0.f));
    //

    // Player
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));
    //

    inventory.init(shaderProgram);

    position = glm::vec2(500, 1300);
	setPosition(position);
}

void Player::update(int deltaTime)
{
	Character::update(deltaTime);
    inventory.update();

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

void Player::render(ShaderProgram &program)
{
    Character::render(program);
    renderHearts(program);
    inventory.render();
}

Item *Player::getSelectedItem() const
{
    return selectedItem;
}

int Player::getSelectedItemIndex() const
{
    return selectedItemIndex;
}

void Player::move(int deltaTime)
{
	bool leftPressed = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
	bool rightPressed = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
	bool bothPressed = leftPressed && rightPressed;
	bool anyPressed = leftPressed || rightPressed;

	if (bothPressed || (velocity.x == 0 && !anyPressed))
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		velocity.x = 0;
	}
	else
	{
		if(leftPressed)
		{
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
            velocity.x = -8;
		}

		if (rightPressed)
		{
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
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
        if (Game::instance().getKeyDown( char('1' + i) ))
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
    TileMap *tmap = Scene::getTileMap();
    glm::ivec2 mousePos = Game::instance().getMousePosWorld();
    if (Game::instance().getMouseLeftButton())
    {
        if (!tmap->getBlock(mousePos) != NULL) // Can it put a block where the mouse is?
        {
            Block *b = selectedItem ? dynamic_cast<Block*>(selectedItem) : NULL;
            if (b != NULL) // Is it a block?
            {
                int amount = b->getAmount();
                if (amount > 0 && tmap->addTile(mousePos, b->getType()))
                {
                    inventory.dropItem(selectedItemIndex);
                }
            }
        }
    }
    else if (Game::instance().getMouseRightButton())
    {
        Block::Type blockType = tmap->getBlock(mousePos);
        if (blockType != NULL)
        {
            switch (blockType)
            {
                case Block::GOLD:     inventory.addItem<BlockGold>();     break;
                case Block::SAPPHIRE: inventory.addItem<BlockSapphire>(); break;
                case Block::RUBY:     inventory.addItem<BlockRuby>();     break;
                case Block::EMERALD:  inventory.addItem<BlockEmerald>();  break;
            }
            tmap->delTile(mousePos);
        }
    }
}

void Player::renderHearts(ShaderProgram &program)
{
    int heartMarginX = 10;
    for (int i = 0; i < maxHealth/2; ++i)
    {
        glm::ivec2 heartPos = heartLinePosition + (heartSize + heartMarginX) * glm::ivec2(i, 0);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(heartPos.x, heartPos.y, 1.f));
        program.setUniformMatrix4f("model", model);
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

void Player::takeDamage()
{
    if (!damaged)
    {
        damaged = true;
        --health;
    }
}
