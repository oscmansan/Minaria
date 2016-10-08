#include "Player.h"
#include "Game.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Block.h"

Player::Player() {}


Player::~Player() {}


void Player::init(ShaderProgram &shaderProgram)
{
	Character::init(shaderProgram);

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

	position = glm::vec2(64, SCREEN_HEIGHT - 400);
	setPosition(position);
}

void Player::update(int deltaTime)
{
	Character::update(deltaTime);

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

	// HANDLE MOUSE ACTIONS
	TileMap *tmap = Scene::getTileMap();
	glm::ivec2 mousePos = Game::instance().getMousePosWorld();
	if (Game::instance().getMouseLeftButtonDown())
	{
		if (!tmap->getBlock(mousePos) != NULL)
		{
            int randBlockType = rand() % 4 + 1;
            int amount = 0;
            switch (randBlockType)
            {
                case Block::TYPE_GOLD:     amount = inventory.getAmount<BlockGold>();     break;
                case Block::TYPE_RUBY:     amount = inventory.getAmount<BlockRuby>();     break;
                case Block::TYPE_EMERALD:  amount = inventory.getAmount<BlockEmerald>();  break;
                case Block::TYPE_SAPPHIRE: amount = inventory.getAmount<BlockSapphire>(); break;
            }

            if (amount > 0 && tmap->addTile(mousePos, randBlockType))
            {
                inventory.dropItem(0);
            }
		}
	}
	else if (Game::instance().getMouseRightButtonDown())
	{
        Block::Type blockType = tmap->getBlock(mousePos);
        if (blockType != NULL)
		{
            switch (blockType)
            {
                case Block::TYPE_GOLD:     inventory.addItem<BlockGold>();     break;
                case Block::TYPE_RUBY:     inventory.addItem<BlockRuby>();     break;
                case Block::TYPE_EMERALD:  inventory.addItem<BlockEmerald>();  break;
                case Block::TYPE_SAPPHIRE: inventory.addItem<BlockSapphire>(); break;
            }
            tmap->delTile(mousePos);
		}
	}
	//
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
			velocity.x = -2;
		}

		if (rightPressed)
		{
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			velocity.x = 2;
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

void Player::takeDamage()
{
	damaged = true;
}
