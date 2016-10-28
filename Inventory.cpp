#include "Inventory.h"

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "ItemSword.h"
#include "SceneGame.h"
#include "ItemPickaxe.h"

Inventory::Inventory()
{
    position = glm::ivec2(5, 5);
    craftingBar = new CraftingBar();
}


Inventory::~Inventory()
{
    delete spriteBg;
    delete spriteSlot;
    delete textureBg;
    delete textureSlot;

    for (Sprite* sp : itemSprites)
    {
        if (sp) delete sp;
    }

    for (Item *it : items)
    {
        if (it) delete it;
    }

    // Dont delete craftingBar
}


void Inventory::init()
{
    isScreen = true;
    Game::getCurrentSceneGame()->addSceneNode(this);
    craftingBar->init();

    program = Game::getCurrentSceneGame()->getShaderProgram();

    textureBg = new Texture();
    textureBg->loadFromFile("images/inventoryBg.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteBg = Sprite::createSprite(size, glm::vec2(1, 1), textureBg, program);
    spriteBg->setNumberAnimations(1);
    spriteBg->addKeyframe(0, glm::vec2(0.0f, 0.f));

    textureSlot = new Texture();
    textureSlot->loadFromFile("images/invSlot.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteSlot = Sprite::createSprite(slotSize, glm::vec2(1, 1), textureSlot, program);
    spriteSlot->setNumberAnimations(1);
    spriteSlot->addKeyframe(0, glm::vec2(0.0f, 0.f));

    for (int i = 0; i < numSlots; ++i)
    {
        glm::ivec2 slotPos = getSlotScreenRect(i).getMin();
        glm::ivec2 slotSize = getSlotScreenRect(i).getSize();
        itemAmountTexts[i]  = Game::getCurrentSceneGame()->createText();

        int slotNumTextSize = 16;
        glm::ivec2 slotNumTextPos = slotPos + glm::ivec2(slotSize.x/2 - slotNumTextSize/2, slotSize.y + 8);
       /* itemSlotNumTexts[i] = Game::getCurrentSceneGame()->createText(std::to_string(i+1),
                                                                      slotNumTextPos,
                                                                      slotNumTextSize);
        */
    }

    addItem<ItemPickaxe>();
    addItem<ItemSword>();
}

void Inventory::renderBackground()
{
    prepareModelViewMatrix();
    //spriteBg->render();
}

void Inventory::renderSlots()
{
    int selectedPos = Game::getCurrentSceneGame()->getPlayer()->getSelectedItemIndex();
    for (int i = 0; i < numSlots; ++i)
    {
        glm::ivec2 slotPos = getSlotScreenRect(i).getMin();

        prepareModelViewMatrix(slotPos);
        spriteSlot->setTint( selectedPos == i ? selectedSlotTint : glm::vec4(1));
        spriteSlot->render();

        prepareModelViewMatrix(slotPos + glm::ivec2(0, slotSize.y + 2),  glm::vec2(1.0f, 0.5f));
        spriteSlot->render();

        Item *it = getItem(i);
        int itAmount = it ? it->getAmount() : 0;
        if (it && itAmount > 0) // Add item texture, if any
        {
            glm::ivec2 itemPos = slotPos + (slotSize - itemSize) / 2;

            Texture *itTexture = it->getItemTexture();

            if (!itemSprites[i])
            {
                itemSprites[i] = Sprite::createSprite(itemSize, it->getSpriteFrame(), itTexture, program);
            }

            itemSprites[i]->setTexture(itTexture);
            int textSize = 11;
            itemAmountTexts[i]->setText(std::to_string(itAmount), textSize);
            itemAmountTexts[i]->setColor(glm::vec4(1,1,1,1));
            itemAmountTexts[i]->setPosition(slotPos + glm::ivec2(0, slotSize.y) + 5);

            prepareModelViewMatrix(itemPos);
            itemSprites[i]->render();
        }
        else
        {
            if (itemAmountTexts[i] && itAmount <= 0)
            {
                itemAmountTexts[i]->setText("");
            }
        }
    }
}

Rect Inventory::getSlotScreenRect(int i) const
{
    int paddingX = (size.x - (slotSize.x * numSlots)) / (numSlots + 1);
    int paddingY = (size.y - slotSize.y) / 2;
    glm::ivec2 padding(paddingX, paddingY);
    glm::ivec2 slotPos = position +
                         (padding + slotSize) * glm::ivec2(i, 0) +
                         padding;
    return Rect(slotPos.x,  slotPos.y,
                slotSize.x, slotSize.y);
}

void Inventory::update(int deltaTime)
{
}

void Inventory::render(ShaderProgram &program)
{
    renderBackground();
    renderSlots();
}

Item *Inventory::getItem(int i) const
{
    return items[i];
}

int Inventory::getNumSlots() const
{
    return numSlots;
}

int Inventory::indexOf(Item *it) const
{
    for (int i = 0; i < items.size(); ++i)
    {
        if (items[i] == it) return i;
    }
    return -1;
}


void Inventory::dropItem(int index)
{
	Item *item = items[index];
    if (item)
    {
        item->decreaseAmount();
        if (item->getAmount() <= 0)
        {
            delete items[index];
            items[index] = NULL;
        }
    }
}

glm::ivec2 Inventory::getSize() const {
    return size;
}

CraftingBar *Inventory::getCraftingBar()
{
    return craftingBar;
}
