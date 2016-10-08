#include "Inventory.h"


Inventory::Inventory()
{
	items = vector<Item*>(5,NULL);
}


Inventory::~Inventory()
{
}


void Inventory::dropItem(int index) 
{
	Item *item = items[index];
	item->decreaseAmount();
	if (item->getAmount() == 0)
	{
		delete items[index];
		items[index] = NULL;
	}
}