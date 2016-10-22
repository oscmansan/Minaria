#include "BombExplosion.h"

#include "Game.h"
#include "SceneGame.h"

Texture* BombExplosion::explosionTexture = NULL;

BombExplosion::BombExplosion()
{
    if (!BombExplosion::explosionTexture)
    {
        BombExplosion::explosionTexture = new Texture();
        BombExplosion::explosionTexture->loadFromFile("images/explosion.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    Game::getCurrentSceneGame()->addSceneNode(this);
}

void BombExplosion::init()
{
    int size = explosionSize;
    float frameSizeX = 0.04f;
    sprite = Sprite::createSprite(glm::ivec2(size), glm::vec2(frameSizeX, 1.0f), BombExplosion::explosionTexture, Game::getCurrentScene()->getShaderProgram());
    setPosition(getPosition() - glm::ivec2(size/2));
    sprite->setNumberAnimations(1);
    sprite->setAnimationSpeed(0, 83);
    for (int i = 0; i < 1.0f / frameSizeX; ++i)
    {
        sprite->addKeyframe(0, glm::vec2(frameSizeX * i, 1.0f));
    }

    sprite->changeAnimation(0);
}

void BombExplosion::update(int deltaTime)
{
    time += deltaTime;
    sprite->update(deltaTime);

    if (time > 280)
    {
        Game::getCurrentSceneGame()->removeSceneNode(this);
    }
}

void BombExplosion::render(ShaderProgram &program)
{
    prepareModelViewMatrix();
    sprite->render();
}