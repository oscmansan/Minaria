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
	vector<Item*> items;

public:
	template<class T>
	void addItem(int subType = -1)
	{
		bool found = false;
		for (int i = 0; i < items.size(); ++i)
		{
			if (dynamic_cast<T*>(items[i]) != NULL)
			{
				items[i]->increaseAmount();
				found = true;
				break;
			}
		}

		if (!found)
		{
			for (int i = 0; i < items.size(); ++i)
			{
				if (items[i] == NULL)
				{
					if (subType == -1) { items[i] = new T(); }
					else { items[i] = new T(subType); }
					break;
				}
			}
		}
	}

	template <class T>
	T* getItem(int subType = -1) const
	{
		for (Item *it : items)
		{
			std::cout << it << std::endl;
			T* specItem = dynamic_cast<T*>(it);
			if (specItem != NULL)
			{
				std::cout << "Found specItem!" << std::endl;
				if (subType == -1) return specItem;
				else
				{
					if (specItem->getSubType() == subType) return specItem;
				}
			}
		}
		return NULL;
	}

	template <class T>
	int getAmount(int subType = -1) const
	{
		Item *it = getItem<T>(subType);
		return (it == NULL) ? 0 : it->getAmount();
	}

	void dropItem(int index);

};

