#include "Inventory.h"

#include "Scene.h"
#include "Player.h"

Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}


void Inventory::init(ShaderProgram &sp)
{
    program = &sp;

    textureBg = new Texture();
    textureBg->loadFromFile("images/inventoryBg.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteBg = Sprite::createSprite(size, glm::vec2(1, 1), textureBg, program);
    spriteBg->setNumberAnimations(1);
    spriteBg->addKeyframe(0, glm::vec2(0.0f, 0.f));

    textureSlot = new Texture();
    textureSlot->loadFromFile("images/inventorySlot.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteSlot = Sprite::createSprite(slotSize, glm::vec2(1, 1), textureSlot, program);
    spriteSlot->setNumberAnimations(1);
    spriteSlot->addKeyframe(0, glm::vec2(0.0f, 0.f));
}

void Inventory::renderBackground()
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.f));
    program->setUniformMatrix4f("model", model);
    program->setUniformMatrix4f("view", glm::mat4(1.0f)); //SS rendering, so no view applied

    spriteBg->render();
}

void Inventory::renderSlots()
{
    program->setUniformMatrix4f("view", glm::mat4(1.0f)); //SS rendering, so no view applied

    int selectedPos = Scene::getPlayer()->getSelectedItemIndex();
    for (int i = 0; i < numSlots; ++i)
    {
        glm::ivec2 slotPos = getSlotScreenRect(i).getMin();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(slotPos.x, slotPos.y, 0.f));
        program->setUniformMatrix4f("model", model);
        spriteSlot->setTint( selectedPos == i ? selectedSlotTint : glm::vec4(1));
        spriteSlot->render();

        Item *it = getItem(i);
        if (it) // Add item texture, if any
        {
            glm::ivec2 itemPos = slotPos + (slotSize - itemSize) / 2;

            Texture *itTexture = it->getItemTexture();
            int itAmount = it->getAmount();
            if (!itemSprites[i])
            {
                itemSprites[i] = Sprite::createSprite(itemSize, glm::vec2(1.0f), itTexture, program);
                itemTexts[i] = Scene::getInstance()->addText();
            }

            itemSprites[i]->setTexture(itTexture);
            int textSize = 16;
            itemTexts[i]->setText(std::to_string(itAmount), textSize);
            itemTexts[i]->setColor(glm::vec4(0,0,0,1));
            itemTexts[i]->setPosition(itemPos + itemSize - textSize - 1);

            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(itemPos.x, itemPos.y, 1.f));
            program->setUniformMatrix4f("model", model);
            itemSprites[i]->render();
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

void Inventory::update()
{

}

void Inventory::render()
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
        if (item->getAmount() == 0)
        {
            delete items[index];
            items[index] = NULL;
        }
    }
}
