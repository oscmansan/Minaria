#pragma once

#include <map>
#include <vector>
#include <iostream>

#include "Item.h"

using namespace std;

class Inventory
{
public:
	Inventory();
	~Inventory();

private:
    vector<Item*> items = vector<Item*>(5, NULL);

public:
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

	template <class T>
    int getAmount() const
	{
        Item *it = getItem<T>();
        return it ? it->getAmount() : 0;
	}

	void dropItem(int index);

};

