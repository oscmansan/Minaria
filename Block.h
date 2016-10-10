#pragma once

#include "Item.h"

class Block : public Item {
public:
    enum Type
    {
        GOLD     = 1,
        SAPPHIRE = 2,
        RUBY     = 3,
        EMERALD  = 4
    };

    enum State {
        FULL = 0,
        MID = 1,
        GONE = 2
    };

    virtual ~Block();
    Type getType() const;
    void hit();
    void restore();

protected:
    Block();
    Type type;
    State state;
    Texture *texture_full;
    Texture *texture_mid;
    Texture *texture_gone;
    Texture *getTexture();
};

class BlockGold : public Block
{
public:
    BlockGold();

private:
    static Texture *texture_full;
    static Texture *texture_mid;
    static Texture *texture_gone;
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
