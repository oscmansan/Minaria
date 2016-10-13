#include "Enemy.h"
#include "Game.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::init(ShaderProgram &shaderProgram)
{
	Character::init(shaderProgram);

	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));

	position = glm::vec2(200, SCREEN_HEIGHT - 80);
	setPosition(position);
	sprite->setTint(glm::vec4(1, 0, 0, 1));
}

void Enemy::update(int deltaTime)
{
	Character::update(deltaTime);

	Player *player = Scene::getPlayer();
	if (player->getBoundingBox().intersects(getBoundingBox()))
	{
		player->takeDamage();
	}
}

void Enemy::move(int deltaTime)
{
	Player *player = Scene::getPlayer();
	if (player->getPosition().x > position.x)
	{
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		velocity.x = 2;
	}
	else
	{
			
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		velocity.x = -2;
	}


	if (player->getPosition().y < position.y && int(Scene::getCurrentTime()) % 1000 < 500)
	{
		jump();
	}

	Character::applyGravity();
}
