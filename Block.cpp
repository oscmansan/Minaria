#include "Block.h"

int Block::TYPE_GOLD = 1;
int Block::TYPE_RUBY = 2;
int Block::TYPE_EMERALD = 3;
int Block::TYPE_SAPPHIRE = 4;

Block::Block()
{
}

Block::Block(int type)
{
	subType = type;
}

Block::~Block()
{
}

int Block::getSubType() const
{
	return subType;
}
