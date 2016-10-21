#ifndef TEMPORARYEFFECT_H
#define TEMPORARYEFFECT_H

#include "Sprite.h"
#include "Texture.h"
#include "ISceneNode.h"

class TemporaryEffect : public ISceneNode
{
protected:
    Sprite *sprite = NULL;
    int lifeTime = 1000;

private:
    float time = 0.0f;

public:

    TemporaryEffect();
    virtual ~TemporaryEffect();

    virtual void init() override;
    virtual void update(int deltaTime) override;
    virtual void render(ShaderProgram &program) override;
};

#endif // TEMPORARYEFFECT_H
