#include "FlyingEnemy.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Game.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Game.h"
#include "Bomb.h"

FlyingEnemy::FlyingEnemy(int posx)
{
    origx = posx;
}

FlyingEnemy::~FlyingEnemy()
{
}

void FlyingEnemy::init()
{
    Enemy::init();

    ShaderProgram *program = Game::getCurrentScene()->getShaderProgram();

    spritesheet.loadFromFile("images/bat.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.215f, 0.4f), &spritesheet, program);
    spritesheet.setWrapS(GL_CLAMP);
    sprite->setNumberAnimations(4);

    sprite->setAnimationSpeed(STAND_LEFT, 8);
    sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0f, 0.0f));

    sprite->setAnimationSpeed(STAND_RIGHT, 8);
    sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0f, 0.5f));

    sprite->setAnimationSpeed(MOVE_LEFT, 8);
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f,  0.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f,  0.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.0f));

    sprite->setAnimationSpeed(MOVE_RIGHT, 8);
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.00f, 0.5f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.23f, 0.5f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.48f, 0.5f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.72f, 0.5f));

    int surfaceLevel = Game::getCurrentSceneGame()->getTileMap()->getSurfaceLevel(origx);
    int origy = surfaceLevel - 200;
    setPosition(glm::ivec2(origx, origy));

    velocity = 3.f * glm::vec2(rand() % 2 - 1, rand() % 2 - 1);
    state = PATROL;
}

void FlyingEnemy::update(int deltaTime)
{
    Character::update(deltaTime);

    Player *player = Game::getCurrentSceneGame()->getPlayer();
    int tileSize = Game::getCurrentSceneGame()->getTileMap()->getTileSize();
    int detectThreshold = 10*tileSize;
    switch(state) {
    case PATROL:
        if (abs(player->getPosition().x - getPosition().x) < detectThreshold) {
            //state = CHASE;
            if (bombTimer == 0) {
                Bomb *b = new Bomb();
                b->setPosition(getPosition());
                glm::vec2 dir = glm::normalize(glm::vec2(player->getPosition() - getPosition()));
                float bombSpeed = 0.1f * glm::min(50.0f, glm::length(glm::vec2(player->getPosition() - getPosition())));
                b->setVelocity(dir * bombSpeed);
                bombTimer = 5000;
            }
        }
        break;
    case CHASE:
        if (abs(player->getPosition().x - getPosition().x) < tileSize) {
            attackPosEnd = player->getPosition();
            attackPosStart = getPosition();
            state = ATTACK_DOWN;
        }
        else if (abs(player->getPosition().x - getPosition().x) > detectThreshold)
            state = PATROL;
        break;
    case ATTACK_DOWN:
        if (glm::distance(glm::vec2(getPosition()),glm::vec2(attackPosEnd)) < 20) {
            if (player->getBoundingBox().intersects(getBoundingBox()))
                player->takeDamage();
            state = ATTACK_UP;
        }
        break;
    case ATTACK_UP:
        if (glm::distance(glm::vec2(getPosition()),glm::vec2(attackPosStart)) == 0)
            state = PATROL;
        break;
    }

    switch(state) {
    case PATROL:
        sprite->setTint(glm::vec4(0,0,1,1));
        break;
    case CHASE:
        sprite->setTint(glm::vec4(0,1,1,1));
        break;
    case ATTACK_DOWN:
        sprite->setTint(glm::vec4(1,0,1,1));
        break;
    case ATTACK_UP:
        sprite->setTint(glm::vec4(1,0,1,1));
        break;
    }

    bombTimer -= deltaTime;
    bombTimer = max(0,bombTimer);
}

void FlyingEnemy::move(int deltaTime)
{
    Player *player = Game::getCurrentSceneGame()->getPlayer();
    //TileMap *tilemap = Game::getCurrentSceneGame()->getTileMap();
    
    if (!dead) {
      float v;
      glm::vec2 dir;
      switch(state) {
      case PATROL:
          v = 1;
          if (int(Scene::getCurrentTime()) % 5000 < 2500) {
              if (sprite->animation() != MOVE_RIGHT)
              sprite->changeAnimation(MOVE_RIGHT);
              velocity.x = v;
          }
          else {
              if (sprite->animation() != MOVE_LEFT)
              sprite->changeAnimation(MOVE_LEFT);
              velocity.x = -v;
          }
          velocity.y = 2*sin(Scene::getCurrentTime()/200);
          break;
      case CHASE:
          v = 3;
          if (player->getPosition().x > getPosition().x) {
              if (sprite->animation() != MOVE_RIGHT)
              sprite->changeAnimation(MOVE_RIGHT);
              velocity.x = v;
          }
          else if (player->getPosition().x < getPosition().x){
              if (sprite->animation() != MOVE_LEFT)
              sprite->changeAnimation(MOVE_LEFT);
              velocity.x = -v;
          }
          break;
      case ATTACK_DOWN:
          v = 5;
          dir = glm::normalize(glm::vec2(attackPosEnd - attackPosStart));
          velocity = v*dir;
          break;
      case ATTACK_UP:
          v = 3;
          dir = glm::normalize(glm::vec2(attackPosStart - attackPosEnd));
          velocity = v*dir;
          break;
      }
    }
    else {
      Enemy::applyGravity();
    }
}
