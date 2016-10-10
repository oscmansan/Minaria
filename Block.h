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
    Type type = Type::GOLD;
    State state = State::FULL;
    Texture *texture_full;
    Texture *texture_mid;
    Texture *texture_gone;
    Texture *getTexture() const;
};

class BlockGold : public Block
{
public:
    BlockGold();

private:
    static Texture *s_texture_full;
    static Texture *s_texture_mid;
    static Texture *s_texture_gone;
};

class BlockSapphire : public Block
{
public:
    BlockSapphire();

private:
    static Texture *s_texture_full;
    static Texture *s_texture_mid;
    static Texture *s_texture_gone;
};

class BlockRuby : public Block
{
public:
    BlockRuby();

private:
    static Texture *s_texture_full;
    static Texture *s_texture_mid;
    static Texture *s_texture_gone;
};

class BlockEmerald : public Block
{
public:
    BlockEmerald();

private:
    static Texture *s_texture_full;
    static Texture *s_texture_mid;
    static Texture *s_texture_gone;
};
