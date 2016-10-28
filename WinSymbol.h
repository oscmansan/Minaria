#ifndef WINSYMBOL_H
#define WINSYMBOL_H

#include "Text.h"
#include "Sprite.h"
#include "Texture.h"
#include "ISceneNode.h"

class WinSymbol : public ISceneNode
{
private:
    Sprite *winSprite = NULL;
    Texture *winTexture = NULL;

public:
    WinSymbol();
    virtual ~WinSymbol();

    int timeSinceBegin = 0;
    float scale = 1.0f;
    float maxScale = 12.0f;

    Text *replayText = NULL;
    float getGrayAmount() const;

    virtual void init() override;
    virtual void update(int deltaTime) override;
    virtual void render(ShaderProgram &program) override;
};

#endif // WINSYMBOL_H
