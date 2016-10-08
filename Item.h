#pragma once

#include <string>
using namespace std;

class Item
{
protected:
	Item();
	virtual ~Item();

private:
	string name = "";
	int amount = 0;

public:
	int getAmount() const;
	void increaseAmount();
	void decreaseAmount();

	friend class Inventory;
};



