#ifndef BOMBEXPLOSION_H
#define BOMBEXPLOSION_H

#include "Sprite.h"
#include "Texture.h"
#include "ISceneNode.h"

class BombExplosion : public ISceneNode
{
private:
    static Texture* explosionTexture;

    Sprite *sprite = NULL;
    float time = 0.0f;

public:
    float explosionSize = 0.0f;

    BombExplosion();

    void init() override;
    void update(int deltaTime) override;
    void render(ShaderProgram &program) override;
};

#endif // BOMBEXPLOSION_H
