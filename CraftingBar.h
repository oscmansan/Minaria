#ifndef CRAFTINGBAR_H
#define CRAFTINGBAR_H

#include <glm/glm.hpp>

#include "ISceneNode.h"

class Text;
class Sprite;
class Texture;
class ShaderProgram;
class CraftingBar : public ISceneNode
{

public:
    CraftingBar();

    virtual void init() override;
    virtual void update(int deltaTime) override;
    virtual void render(ShaderProgram &program) override;

private:
    const int CraftingSlotSize = 32;

    Text *craftingText = NULL;

    glm::ivec2 swordPosition;
    Texture *swordTexture = NULL;
    Sprite *spriteSword =  NULL;


    glm::ivec2 bombPosition;
    Texture *bombTexture = NULL;
    Sprite *spriteBomb =  NULL;

    Texture *textureSlot = NULL;
    Sprite *spriteSlot =  NULL;
};

#endif // CRAFTINGBAR_H
