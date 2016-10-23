#pragma once

#include <string>
#include <glm/glm.hpp>

#include "Texture.h"

using namespace std;

class Item
{
protected:
	Item();
	virtual ~Item();

    Texture *itemTexture = NULL;

private:
	string name = "";
    int amount = 0;

public:
    virtual Texture* getItemTexture() const;
    virtual glm::vec2 getSpriteFrame() const { return glm::vec2(1.0f); }

	int getAmount() const;
	void increaseAmount();
    void decreaseAmount();

    friend class Inventory;
};



