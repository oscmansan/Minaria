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

    setPosition(glm::ivec2(700, 2000));

    movTime = 1000;
}

void FlyingEnemy::update(int deltaTime)
{
    Enemy::update(deltaTime);
    movTime -= deltaTime;
    movTime = max(0,movTime);
}

void FlyingEnemy::move(int deltaTime)
{
    if (!dead)
    {
        if (movTime > 0) return;

        movTime = 1000;

        float v = 1;
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
    else
    {
        Enemy::applyGravity();
    }
}
