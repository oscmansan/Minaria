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
    virtual ~CraftingBar();

    virtual void init() override;
    virtual void update(int deltaTime) override;
    virtual void render(ShaderProgram &program) override;

    glm::ivec2 getSize() const override;

private:
    const int CraftingSlotSize = 32;
    const glm::ivec2 OverlaySize = glm::ivec2(96, 50);
    glm::ivec2 OverlayPos;

    Text *craftingText = NULL;

    glm::ivec2 swordPosition;
    Texture *swordTexture = NULL;
    Sprite *spriteSword =  NULL;
    Texture *swordOverlayTexture = NULL;
    Sprite *spriteSwordOverlay =  NULL;
    Sprite *spriteSlotSword =  NULL;


    glm::ivec2 bombPosition;
    Texture *bombTexture = NULL;
    Sprite *spriteBomb =  NULL;
    Texture *bombOverlayTexture = NULL;
    Sprite *spriteBombOverlay =  NULL;
    Sprite *spriteSlotBomb = NULL;

    Texture *textureSlot = NULL;
};

#endif // CRAFTINGBAR_H
