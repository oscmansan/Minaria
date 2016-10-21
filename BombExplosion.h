#ifndef BOMBEXPLOSION_H
#define BOMBEXPLOSION_H

#include "Texture.h"
#include "TemporaryEffect.h"

class BombExplosion : public TemporaryEffect
{
private:
    static Texture* explosionTexture;

public:
    float explosionSize = 0.0f;

    BombExplosion();

    void init() override;
    void update(int deltaTime) override;
    void render(ShaderProgram &program) override;
};

#endif // BOMBEXPLOSION_H
