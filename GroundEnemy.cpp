#include "GroundEnemy.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Game.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Game.h"

GroundEnemy::GroundEnemy() {}

GroundEnemy::~GroundEnemy() {}

void GroundEnemy::init()
{
    Enemy::init();

    ShaderProgram *program = Game::getCurrentScene()->getShaderProgram();

    spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, program);
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

    setPosition(glm::ivec2(1000, 0));
    sprite->setTint(glm::vec4(1, 0, 0, 1));

    state = PATROL;
    jumpSpeed = -5;
}

void GroundEnemy::update(int deltaTime)
{
    Enemy::update(deltaTime);

    Player *player = Game::getCurrentSceneGame()->getPlayer();

    int tileSize = Game::getCurrentSceneGame()->getTileMap()->getTileSize();
    int detectThreshold = 10*tileSize;
    switch(state) {
        case PATROL:
            if (abs(player->getPosition().x - getPosition().x) < detectThreshold)
                state = CHASE;
            break;
        case CHASE:
            if (abs(player->getPosition().x - getPosition().x) < tileSize)
                state = ATTACK;
            else if (abs(player->getPosition().x - getPosition().x) > detectThreshold)
                state = PATROL;
            break;
        case ATTACK:
            if (abs(player->getPosition().x - getPosition().x) > tileSize)
                state = PATROL;
            if (player->getBoundingBox().intersects(getBoundingBox()))
                player->takeDamage();
            break;
    }

    switch(state) {
        case PATROL:
            sprite->setTint(glm::vec4(0,0,1,1));
            break;
        case CHASE:
            sprite->setTint(glm::vec4(0,1,1,1));
            break;
        case ATTACK:
            sprite->setTint(glm::vec4(1,0,1,1));
            break;
    }
}

void GroundEnemy::move(int deltaTime)
{
    Player *player = Game::getCurrentSceneGame()->getPlayer();
    TileMap *tilemap = Game::getCurrentSceneGame()->getTileMap();

    if (!dead)
    {
        if (tilemap->collisionMoveLeft(getPosition()+glm::ivec2(-5,0),getSize()) or
                tilemap->collisionMoveRight(getPosition()+glm::ivec2(5,0),getSize()))
            jump();

        switch(state) {
            float v;
            case PATROL:
                v = 1;
                if (int(Scene::getCurrentTime()) % 3000 < 1500) {
                    if (sprite->animation() != MOVE_RIGHT)
                        sprite->changeAnimation(MOVE_RIGHT);
                    velocity.x = v;
                }
                else {
                    if (sprite->animation() != MOVE_LEFT)
                        sprite->changeAnimation(MOVE_LEFT);
                    velocity.x = -v;
                }
                break;
            case CHASE:
                v = 3;
                if (player->getPosition().x > getPosition().x) {
                    if (sprite->animation() != MOVE_RIGHT)
                        sprite->changeAnimation(MOVE_RIGHT);
                    velocity.x = v;
                }
                else {
                    if (sprite->animation() != MOVE_LEFT)
                        sprite->changeAnimation(MOVE_LEFT);
                    velocity.x = -v;
                }
                break;
            case ATTACK:
                break;
        }
    }
    else
    {

    }

    Enemy::applyGravity();
}