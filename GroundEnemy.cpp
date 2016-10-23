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

    spritesheet.loadFromFile("images/miner.png", TEXTURE_PIXEL_FORMAT_RGBA);
    float sizeFactor = ((rand() % 10) / 100.0f * (rand()%2 == 0 ? 1 : -1)) + 1.0f;
    sprite = Sprite::createSprite(glm::ivec2(int(36 * sizeFactor), int(48 * sizeFactor)), glm::vec2(0.075f, 0.23f), &spritesheet, program);
    sprite->setNumberAnimations(5);

    sprite->setAnimationSpeed(STAND_LEFT, 8);
    sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.51f));

    sprite->setAnimationSpeed(STAND_RIGHT, 8);
    sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0f, 0.75f));

    sprite->setAnimationSpeed(MOVE_LEFT, 8);
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.51f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.1f, 0.51f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f, 0.51f));

    sprite->setAnimationSpeed(MOVE_RIGHT, 8);
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f, 0.75f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.1f, 0.75f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f, 0.75f));

    sprite->setAnimationSpeed(DEAD, 1);
    sprite->addKeyframe(DEAD, glm::vec2(0.575f, 0.515f));

    setPosition(glm::ivec2(700, 1000));
    sprite->setTint(glm::vec4(1, 0, 0, 1));

    state = PATROL;
    jumpSpeed = -5;
}

void GroundEnemy::update(int deltaTime)
{
    Enemy::update(deltaTime);

    if (dead) return;

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

    /*
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
    */
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

    Enemy::applyGravity();
}
