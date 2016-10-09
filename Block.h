#pragma once

#include "Item.h"

class Block :
	public Item
{
public:
    enum Type
    {
        TYPE_GOLD     = 1,
        TYPE_SAPPHIRE = 2,
        TYPE_RUBY     = 3,
        TYPE_EMERALD  = 4
    };

    virtual ~Block();
    Type getType() const;

protected:
    Block();
    Type type;
};

class BlockGold : public Block
{
public:
    BlockGold();
};

class BlockSapphire : public Block
{
public:
    BlockSapphire();
};

class BlockRuby : public Block
{
public:
    BlockRuby();
};

class BlockEmerald : public Block
{
public:
    BlockEmerald();
};
