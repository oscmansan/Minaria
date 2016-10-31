#include "Enemy.h"

#include "Game.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

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

Rect Enemy::getBoundingBox() const
{
    if (dead) return Rect(0,0,0,0);
    else return Character::getBoundingBox();
}

void Enemy::takeDamage(int damage)
{
    beginToDie();
}

void Enemy::beginToDie()
{
    dead = true;
    velocity.x = 0.0f;
    sprite->changeAnimation(DEAD);
}

void Enemy::die()
{
    Game::getCurrentSceneGame()->removeSceneNode(this);
    Game::getCurrentSceneGame()->removeCharacter(this);
}
