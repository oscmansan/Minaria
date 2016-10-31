#ifndef BOMBEXPLOSION_H
#define BOMBEXPLOSION_H

#include "Texture.h"
#include "TemporaryEffect.h"

class BombExplosion : public TemporaryEffect
{
private:
    static Texture* orangeTexture;
    static Texture* purpleTexture;
    bool color;

public:
    float explosionSize = 0.0f;

    BombExplosion(bool color);

    void init() override;
    void update(int deltaTime) override;
    void render(ShaderProgram &program) override;
};

#endif // BOMBEXPLOSION_H
