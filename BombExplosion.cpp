#include "BombExplosion.h"

#include "Game.h"
#include "SceneGame.h"

Texture* BombExplosion::explosionTexture = NULL;

BombExplosion::BombExplosion()
{
    if (!BombExplosion::explosionTexture)
    {
        BombExplosion::explosionTexture = new Texture();
        BombExplosion::explosionTexture->loadFromFile("images/explosion2.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    lifeTime = 280;
}

void BombExplosion::init()
{
    TemporaryEffect::init();

    int size = explosionSize;
    float frameSizeX = 0.25f;
    float frameSizeY = 0.25f;
    sprite = Sprite::createSprite(glm::ivec2(size), glm::vec2(frameSizeX, frameSizeY), BombExplosion::explosionTexture, Game::getCurrentScene()->getShaderProgram());
    setPosition(getPosition() - glm::ivec2(size/2));
    sprite->setNumberAnimations(1);
    sprite->setAnimationSpeed(0, 40);
    for (int i = 0; i < 1.0f / frameSizeY; ++i)
    {
        for (int j = 0; j < 1.0f / frameSizeX; ++j)
        {
            sprite->addKeyframe(0, glm::vec2(frameSizeX * j, frameSizeY * i));
        }
    }

    sprite->changeAnimation(0);
    Game::getCurrentSceneGame()->getSoundManager()->playSound("../sounds/explosion.wav");
}

void BombExplosion::update(int deltaTime)
{
    TemporaryEffect::update(deltaTime);
}

void BombExplosion::render(ShaderProgram &program)
{
    TemporaryEffect::render(program);
}
