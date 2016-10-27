#include "Character.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "TileMap.h"
#include "Game.h"

Character::Character()
{
    Game::getCurrentScene()->addSceneNode(this);
}

Character::~Character()
{
    delete sprite;
}

void Character::move(int deltaTime)
{
}

void Character::init()
{
    bJumping = false;

	jumpSpeed = -9.0f;
	gravity = 0.4f;
    maxFallSpeed = 3.0f;
}

bool Character::isGrounded()
{
	position.y += 1;
	int y = position.y;
	bool grounded = map->collisionMoveDown(position, sprite->getSize(), &y);
	position.y -= 1;
	return grounded;
}

void Character::processCollisions()
{
	glm::ivec2 spriteSize = sprite->getSize();

	if (map->collisionMoveLeft(position, spriteSize))
	{
		position.x -= velocity.x;
		velocity.x = 0;
	}

	if (map->collisionMoveRight(position, spriteSize))
	{
		position.x -= velocity.x;
		velocity.x = 0;
	}

	// This must go after
	if (map->collisionMoveDown(position, spriteSize, &position.y))
	{
		velocity.y = 0;
		bJumping = false;
	}

	if (map->collisionMoveUp(position, spriteSize, &position.y))
	{
		velocity.y = 0;
	}

	// Solves a bug when you jump with collision tiles up and down
	if (bJumping && isGrounded()) 
	{
		bJumping = false;
	}
}

void Character::jump()
{
    if (!bJumping)
	{
		bJumping = true;
		velocity.y = jumpSpeed;
	}
}

void Character::applyGravity() 
{
	if (!isGrounded())
	{
		velocity.y += gravity;    // Apply gravity
		velocity.y = glm::min(maxFallSpeed, velocity.y);
	}
}

void Character::update(int deltaTime)
{
	sprite->update(deltaTime);

	move(deltaTime); // Apply movement
	setPosition(getPosition() + glm::ivec2(velocity.x, velocity.y)); // Apply movement
    processCollisions(); // Collision check

	setPosition(position);
}

glm::ivec2 Character::getSize()
{
    return sprite->getSize();
}

glm::ivec2 Character::getScreenPosition() const
{
    return position - Game::getCurrentSceneGame()->getCamera()->getPosition();
}

Rect Character::getBoundingBox() const
{
	glm::ivec2 spriteSize = sprite->getSize();
	return Rect(position.x,   position.y, 
		        spriteSize.x, spriteSize.y);
}

glm::vec2 Character::getVelocity() const
{
    return velocity;
}

void Character::render(ShaderProgram &program)
{
    prepareModelViewMatrix();
	sprite->render();
}

void Character::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}




