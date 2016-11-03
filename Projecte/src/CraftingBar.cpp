#include "CraftingBar.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"
#include "Text.h"
#include "Game.h"
#include "Sprite.h"
#include "Texture.h"
#include "ItemBomb.h"
#include "ItemSword.h"

CraftingBar::CraftingBar()
{
    isScreen = true;
}

CraftingBar::~CraftingBar()
{
    delete swordTexture;
    delete bombTexture;
    delete swordOverlayTexture;
    delete spriteSwordOverlay;
    delete spriteSword;
    delete spriteBomb;
    delete bombOverlayTexture;
    delete spriteBombOverlay;
}

void CraftingBar::init()
{
    ShaderProgram *program = Game::getCurrentSceneGame()->getShaderProgram();
    Game::getCurrentScene()->addSceneNode(this);


    textureSlot = new Texture();
    textureSlot->loadFromFile("images/invSlot.png", TEXTURE_PIXEL_FORMAT_RGBA);

    swordPosition = glm::ivec2(Game::getScreenWidth() - 64, Game::getScreenHeight() - 64);
    swordTexture = new Texture();
    swordTexture->loadFromFile("images/sword.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteSword = Sprite::createSprite(glm::ivec2(glm::vec2(CraftingSlotSize) * 0.8f), glm::vec2(1.0f), swordTexture, program);

    swordOverlayTexture = new Texture();
    swordOverlayTexture->loadFromFile("images/slotCraftingOverlaySword.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteSwordOverlay = Sprite::createSprite(glm::ivec2(glm::vec2(OverlaySize) * 0.8f), glm::vec2(1.0f), swordOverlayTexture, program);
    spriteSlotSword = Sprite::createSprite(glm::ivec2(CraftingSlotSize), glm::vec2(1.0f), textureSlot, program);

    bombPosition = glm::ivec2(Game::getScreenWidth() - 112, swordPosition.y);
    bombTexture = new Texture();
    bombTexture->loadFromFile("images/bomb.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteBomb = Sprite::createSprite(glm::ivec2(glm::vec2(CraftingSlotSize) * 0.8f), glm::vec2(1.0f), bombTexture, program);

    position = bombPosition;

    bombOverlayTexture = new Texture();
    bombOverlayTexture->loadFromFile("images/slotCraftingOverlayBomb.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteBombOverlay = Sprite::createSprite(glm::ivec2(glm::vec2(OverlaySize) * 0.8f), glm::vec2(1.0f), bombOverlayTexture, program);
    spriteSlotBomb = Sprite::createSprite(glm::ivec2(CraftingSlotSize), glm::vec2(1.0f), textureSlot, program);

    craftingText = Game::getCurrentSceneGame()->createText("CRAFTING", bombPosition + glm::ivec2(-10, -24), 12);

    OverlayPos = bombPosition - glm::ivec2(OverlaySize.x + 5, 0);
}

void CraftingBar::update(int deltaTime)
{
    glm::ivec2 mousePos = Game::instance().getMousePosScreen();
    Rect swordRect(swordPosition.x, swordPosition.y, spriteSlotSword->getSize().x, spriteSlotSword->getSize().y);
    Rect bombRect(bombPosition.x, bombPosition.y, spriteSlotBomb->getSize().x, spriteSlotBomb->getSize().y);

    spriteSword->setTint(glm::vec4(1.0f));
    spriteBomb->setTint(glm::vec4(1.0f));
    spriteSlotSword->setTint(glm::vec4(1.0f));
    spriteSlotBomb->setTint(glm::vec4(1.0f));

    Inventory *inv = Game::getCurrentSceneGame()->getPlayer()->getInventory();
    bool canCraftBomb  = inv->getAmount<BlockWood>() >= 5;
    bool canCraftSword = inv->getAmount<BlockPurple>() >= 4;
    const glm::vec4 hoverTint = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
    if (swordRect.contains(mousePos))
    {
        if (canCraftSword && Game::instance().getMouseLeftButtonDown())
        {
            Game::getCurrentSceneGame()->getPlayer()->getInventory()->addItem<ItemSword>();
            inv->drop<BlockPurple>(4);
        }
        spriteSlotSword->setTint(hoverTint);
    }
    else if (bombRect.contains(mousePos))
    {
        if (canCraftBomb && Game::instance().getMouseLeftButtonDown())
        {
            for (int i = 0; i < 20; ++i) inv->addItem<ItemBomb>();
            inv->drop<BlockWood>(5);
        }
        spriteSlotBomb->setTint(hoverTint);
    }

    const float fadeCantCraft = 0.3f;
    if (!canCraftSword)
    {
            spriteSlotSword->setTint(spriteSlotSword->getTint() * fadeCantCraft);
            spriteSword->setTint(spriteSword->getTint() * fadeCantCraft);
}
    if (!canCraftBomb)
    {
            spriteSlotBomb->setTint(spriteSlotBomb->getTint() * fadeCantCraft);
            spriteBomb->setTint(spriteBomb->getTint() * fadeCantCraft);
    }
}

void CraftingBar::render(ShaderProgram &program)
{
    Inventory *inv = Game::getCurrentSceneGame()->getPlayer()->getInventory();

    prepareModelViewMatrix(swordPosition);
    spriteSlotSword->render();
    prepareModelViewMatrix(swordPosition + (CraftingSlotSize-spriteSword->getSize())/2);
    spriteSword->render();

    prepareModelViewMatrix(bombPosition);
    spriteSlotBomb->render();
    prepareModelViewMatrix(bombPosition + (CraftingSlotSize-spriteBomb->getSize())/2);
    spriteBomb->render();

    glm::ivec2 mousePos = Game::instance().getMousePosScreen();
    Rect swordRect(swordPosition.x, swordPosition.y, spriteSlotSword->getSize().x, spriteSlotSword->getSize().y);
    Rect bombRect(bombPosition.x, bombPosition.y, spriteSlotBomb->getSize().x, spriteSlotBomb->getSize().y);
    if (swordRect.contains(mousePos))
    {
        prepareModelViewMatrix(OverlayPos);
        spriteSwordOverlay->render();
    }
    else if (bombRect.contains(mousePos))
    {
        prepareModelViewMatrix(OverlayPos);
        spriteBombOverlay->render();
    }
}

glm::ivec2 CraftingBar::getSize() const
{
    return (swordPosition + spriteSlotSword->getSize()) - bombPosition;
}
