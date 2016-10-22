#include "Enemy.h"

#include "Game.h"

Enemy::Enemy()
{
}

Enemy::~Enemy() {}

void Enemy::init()
{
    Character::init();
}

void Enemy::update(int deltaTime)
{
    Character::update(deltaTime);
    if (dead)
    {
        timeSinceDead += deltaTime;
        if (timeSinceDead > 2000)
        {
            die();
        }
    }
}

void Enemy::move(int deltaTime)
{
    Character::move(deltaTime);
}

void Enemy::takeDamage(int damage)
{
    beginToDie();
    rotation = -3.141592f / 2;
}


void Enemy::beginToDie()
{
    dead = true;
    velocity.x = 0.0f;
}

void Enemy::die()
{
    Game::getCurrentSceneGame()->removeSceneNode(this);
    Game::getCurrentSceneGame()->removeCharacter(this);
}
