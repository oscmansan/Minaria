#include "FlyingEnemy.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Game.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Game.h"

FlyingEnemy::FlyingEnemy() {};

FlyingEnemy::~FlyingEnemy() {};

void FlyingEnemy::init(ShaderProgram &shaderProgram)
{
    Character::init(shaderProgram);

    spritesheet.loadFromFile("images/bub_bad.png", TEXTURE_PIXEL_FORMAT_RGBA);
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

    setPosition(glm::ivec2(1000, 2100));

    velocity = 3.f*glm::vec2(rand()%2-1,rand()%2-1);
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
            if (abs(player->getPosition().x - getPosition().x) < detectThreshold)
                state = CHASE;
            break;
        case CHASE:
            if (abs(player->getPosition().x - getPosition().x) < tileSize) {
                state = ATTACK_DOWN;
                attackPosStart = getPosition();
                attackPosEnd = player->getPosition();
            }
            else if (abs(player->getPosition().x - getPosition().x) > detectThreshold)
                state = PATROL;
            break;
        case ATTACK_DOWN:
            if (glm::distance(glm::vec2(getPosition()),glm::vec2(attackPosEnd)) < 30) {
                if (player->getBoundingBox().intersects(getBoundingBox()))
                    player->takeDamage();
                state = ATTACK_UP;
            }
            break;
        case ATTACK_UP:
            if (glm::distance(glm::vec2(getPosition()),glm::vec2(attackPosStart)) < 30)
                state = PATROL;
    }
    cout << state << endl;
}

void FlyingEnemy::randomFly() {
    float v = 3;

    int mov = rand() % 4;
    switch (mov) {
    case 0:
        if (sprite->animation() != MOVE_RIGHT)
            sprite->changeAnimation(MOVE_RIGHT);
        velocity.x = v;
        break;
    case 1:
        if (sprite->animation() != MOVE_LEFT)
            sprite->changeAnimation(MOVE_LEFT);
        velocity.x = -v;
        break;
    case 2:
        if (sprite->animation() != MOVE_RIGHT)
            sprite->changeAnimation(MOVE_RIGHT);
        velocity.y = v;
        break;
    case 3:
        if (sprite->animation() != MOVE_LEFT)
            sprite->changeAnimation(MOVE_LEFT);
        velocity.y = -v;
        break;
    }
}

void FlyingEnemy::move(int deltaTime)
{
    Player *player = Game::getCurrentSceneGame()->getPlayer();
    TileMap *tilemap = Game::getCurrentSceneGame()->getTileMap();

    // Detect collisions
    /*if (tilemap->collisionMoveRight(getPosition()+glm::ivec2(5,0),getSize()))
        velocity.x = -velocity.x;
    if (tilemap->collisionMoveLeft(getPosition()+glm::ivec2(-5,0),getSize()))
        velocity.x = -velocity.x;
    if (tilemap->collisionMoveUp(getPosition()+glm::ivec2(0,5),getSize(),NULL))
        velocity.y= -velocity.y;
    if (tilemap->collisionMoveDown(getPosition()+glm::ivec2(0,-5),getSize(),NULL))
        velocity.y = -velocity.y;*/

    float v;
    glm::vec2 dir;
    switch(state) {
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
        else if (player->getPosition().x < getPosition().x){
            if (sprite->animation() != MOVE_LEFT)
                sprite->changeAnimation(MOVE_LEFT);
            velocity.x = -v;
        }
        break;
    case ATTACK_DOWN:
        v = 5;
        dir = glm::normalize(glm::vec2(attackPosEnd - getPosition()));
        velocity = v*dir;
        break;
    case ATTACK_UP:
        v = 3;
        dir = glm::normalize(glm::vec2(attackPosStart - getPosition()));
        velocity = v*dir;
        break;
    }
}
