#pragma once

#include <map>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Item.h"
#include "Sprite.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Rect.h"

using namespace std;

class Inventory
{
public:
	Inventory();
	~Inventory();

private:
    const int numSlots = 7;
    vector<Item*> items = vector<Item*>(numSlots, NULL);

    const glm::ivec2 position = glm::ivec2(15, 15);
    const glm::ivec2 size = glm::ivec2(200, 25);
    const glm::ivec2 slotSize = glm::ivec2(20, 20);
    const glm::ivec2 itemSize = glm::ivec2(15, 15);

    ShaderProgram *program = nullptr;
    Texture *textureBg = nullptr;
    Texture *textureSlot = nullptr;
    Sprite *spriteBg   = nullptr;
    Sprite *spriteSlot = nullptr;

    glm::vec4 selectedSlotTint = glm::vec4(1, 0, 0, 0.5f);

    void renderBackground();
    void renderSlots();

public:

    void init(ShaderProgram &sp);

    void update();
    void render();

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

