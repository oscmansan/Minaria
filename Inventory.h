#pragma once

#include <map>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Rect.h"
#include "Text.h"
#include "Item.h"
#include "Sprite.h"
#include "Texture.h"
#include "ISceneNode.h"
#include "CraftingBar.h"
#include "ShaderProgram.h"

using namespace std;

class Inventory : public ISceneNode
{
public:
	Inventory();
	~Inventory();

private:
    CraftingBar craftingBar;

    const int numSlots = 7;
    vector<Item*> items = vector<Item*>(numSlots, NULL);
    vector<Sprite*> itemSprites = vector<Sprite*>(numSlots, NULL);
    vector<Text*> itemAmountTexts   = vector<Text*>(numSlots, NULL);
    vector<Text*> itemSlotNumTexts   = vector<Text*>(numSlots, NULL);

    const glm::ivec2 size = glm::ivec2(400, 50);
    const glm::ivec2 slotSize = glm::ivec2(40, 40);
    const glm::ivec2 itemSize = glm::ivec2(30, 30);

    ShaderProgram *program = nullptr;
    Texture *textureBg = nullptr;
    Texture *textureSlot = nullptr;
    Sprite *spriteBg   = nullptr;
    Sprite *spriteSlot = nullptr;

    glm::vec4 selectedSlotTint = glm::vec4(1, 0, 0, 0.5f);

    void renderBackground();
    void renderSlots();

public:

    virtual void init() override;
    virtual void update(int deltaTime) override;
    virtual void render(ShaderProgram &program) override;

	template<class T>
    void addItem()
	{
        Item *it = getItem<T>();
        if (!it)
        {
			for (int i = 0; i < items.size(); ++i)
            {
				if (items[i] == NULL)
                {
                    it = items[i] = new T();
					break;
				}
			}
		}
        it->increaseAmount();
	}

	template <class T>
    T* getItem() const
	{
		for (Item *it : items)
        {
			T* specItem = dynamic_cast<T*>(it);
			if (specItem != NULL)
            {
                return specItem;
			}
		}
		return NULL;
    }

    Item* getItem(int i) const;

	template <class T>
    int getAmount() const
	{
        Item *it = getItem<T>();
        return it ? it->getAmount() : 0;
    }

    template <class T>
    int indexOf() const
    {
        Item *it = getItem<T>();
        return indexOf(it);
    }

    Rect getSlotScreenRect(int i) const;

    int getNumSlots() const;

    int indexOf(Item *it) const;
	void dropItem(int index);

};

