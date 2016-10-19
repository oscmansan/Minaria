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

    setPosition(glm::ivec2(700, 1300));
    sprite->setTint(glm::vec4(1, 0, 0, 1));

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
