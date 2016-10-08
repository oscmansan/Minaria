#pragma once
#include "Item.h"
class Block :
	public Item
{
private:
	int subType;

public:
	static int TYPE_GOLD;
	static int TYPE_RUBY;
	static int TYPE_EMERALD;
	static int TYPE_SAPPHIRE;

	Block();
	Block(int type);
	virtual ~Block();

	int getSubType() const;

	bool operator==(Block *block) const;
};