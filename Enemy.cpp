#include "Enemy.h"

#include "Game.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::hit()
{
    Game::getCurrentSceneGame()->destroyCharacter(this);
}
