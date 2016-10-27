#include "BombExplosion.h"

#include "Game.h"
#include "SceneGame.h"

Texture* BombExplosion::orangeTexture = NULL;
Texture* BombExplosion::purpleTexture = NULL;

BombExplosion::BombExplosion(bool color)
{
    if (!BombExplosion::orangeTexture)
    {
        BombExplosion::orangeTexture = new Texture();
        BombExplosion::orangeTexture->loadFromFile("images/explosion2.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!BombExplosion::purpleTexture) {
        BombExplosion::purpleTexture = new Texture();
        BombExplosion::purpleTexture->loadFromFile("images/explosion3.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    this->color = color;
    lifeTime = 280;
}

void BombExplosion::init()
{
    TemporaryEffect::init();

    int size = explosionSize;
    float frameSizeX = 0.25f;
    float frameSizeY = 0.25f;
    Texture* texture = color ? BombExplosion::purpleTexture : BombExplosion::orangeTexture;
    sprite = Sprite::createSprite(glm::ivec2(size), glm::vec2(frameSizeX, frameSizeY), texture, Game::getCurrentScene()->getShaderProgram());
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
    Game::getCurrentSceneGame()->getSoundManager()->playSound("../sounds/explosion.wav",50.f);
}

void BombExplosion::update(int deltaTime)
{
    TemporaryEffect::update(deltaTime);
}

void BombExplosion::render(ShaderProgram &program)
{
    TemporaryEffect::render(program);
}
