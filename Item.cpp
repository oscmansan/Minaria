#include "Item.h"


Item::Item()
{
}

Item::~Item()
{
}

int Item::getAmount() const {
	return amount;
}

void Item::increaseAmount() {
	++amount;
}

void Item::decreaseAmount() {
	--amount;
}