#include "CraftingBar.h"

#include <glm/gtc/matrix_transform.hpp>

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

    swordPosition = glm::ivec2(Game::getScreenWidth() - 64, Game::getScreenHeight() - 64);
    swordTexture = new Texture();
    swordTexture->loadFromFile("images/sword.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteSword = Sprite::createSprite(glm::ivec2(glm::vec2(CraftingSlotSize) * 0.8f), glm::vec2(1.0f), swordTexture, program);

    swordOverlayTexture = new Texture();
    swordOverlayTexture->loadFromFile("images/sword.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteSwordOverlay = Sprite::createSprite(glm::ivec2(glm::vec2(OverlaySize) * 0.8f), glm::vec2(1.0f), swordTexture, program);

    bombPosition = glm::ivec2(Game::getScreenWidth() - 112, swordPosition.y);
    bombTexture = new Texture();
    bombTexture->loadFromFile("images/bomb.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteBomb = Sprite::createSprite(glm::ivec2(glm::vec2(CraftingSlotSize) * 0.8f), glm::vec2(1.0f), bombTexture, program);

    bombOverlayTexture = new Texture();
    bombOverlayTexture->loadFromFile("images/sword.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteBombOverlay = Sprite::createSprite(glm::ivec2(glm::vec2(OverlaySize) * 0.8f), glm::vec2(1.0f), swordTexture, program);

    textureSlot = new Texture();
    textureSlot->loadFromFile("images/invSlot.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteSlot = Sprite::createSprite(glm::ivec2(CraftingSlotSize), glm::vec2(1.0f), textureSlot, program);

    craftingText = Game::getCurrentSceneGame()->createText("CRAFTING", bombPosition + glm::ivec2(-10, -16), 12);
}

void CraftingBar::update(int deltaTime)
{
    glm::ivec2 mousePos = Game::instance().getMousePosScreen();

    Rect swordRect(swordPosition.x, swordPosition.y, spriteSlot->getSize().x, spriteSlot->getSize().y);
    Rect bombRect(bombPosition.x, bombPosition.y, spriteSlot->getSize().x, spriteSlot->getSize().y);
    if (swordRect.contains(mousePos))
    {
        if (Game::instance().getMouseLeftButtonDown())
        {
            Game::getCurrentSceneGame()->getPlayer()->getInventory()->addItem<ItemSword>();
        }
    }
    else if (bombRect.contains(mousePos))
    {
        if (Game::instance().getMouseLeftButtonDown())
        {
            Game::getCurrentSceneGame()->getPlayer()->getInventory()->addItem<ItemBomb>();
        }
    }
}

void CraftingBar::render(ShaderProgram &program)
{
    prepareModelViewMatrix(swordPosition);
    spriteSlot->render();
    prepareModelViewMatrix(swordPosition + (CraftingSlotSize-spriteSword->getSize())/2);
    spriteSword->render();

    prepareModelViewMatrix(bombPosition);
    spriteSlot->render();
    prepareModelViewMatrix(bombPosition + (CraftingSlotSize-spriteBomb->getSize())/2);
    spriteBomb->render();
}
