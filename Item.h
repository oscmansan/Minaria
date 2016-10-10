#pragma once

#include <string>

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
    Texture* getItemTexture() const;
	int getAmount() const;
	void increaseAmount();
	void decreaseAmount();

	friend class Inventory;
};



