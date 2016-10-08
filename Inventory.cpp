#include "Inventory.h"


Inventory::Inventory()
{
}


Inventory::~Inventory()
{
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
