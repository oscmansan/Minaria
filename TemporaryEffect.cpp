#include "TemporaryEffect.h"

#include "Game.h"
#include "SceneGame.h"

TemporaryEffect::TemporaryEffect()
{
    Game::getCurrentSceneGame()->addSceneNode(this);
}

TemporaryEffect::~TemporaryEffect()
{
    delete sprite;
}

void TemporaryEffect::init()
{
}

void TemporaryEffect::update(int deltaTime)
{
    time += deltaTime;
    sprite->update(deltaTime);

    if (time > lifeTime)
    {
        Game::getCurrentSceneGame()->removeSceneNode(this);
    }
}

void TemporaryEffect::render(ShaderProgram &program)
{
    prepareModelViewMatrix();
    sprite->render();
}
