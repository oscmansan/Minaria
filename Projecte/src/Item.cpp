#include "Item.h"


Item::Item()
{
}

Item::~Item()
{
}

Texture* Item::getItemTexture() const
{
    return itemTexture;
}

int Item::getAmount() const
{
    return amount;
}

void Item::increaseAmount()
{
	++amount;
}

void Item::decreaseAmount()
{
	--amount;
}
