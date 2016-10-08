#pragma once

#include "Item.h"

class Block :
	public Item
{
public:
    enum Type
    {
        TYPE_GOLD,
        TYPE_RUBY,
        TYPE_EMERALD,
        TYPE_SAPPHIRE
    };

    Block();
    virtual ~Block();
};

class BlockGold     : public Block {};
class BlockRuby     : public Block {};
class BlockEmerald  : public Block {};
class BlockSapphire : public Block {};
