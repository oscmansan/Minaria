#pragma once

#include "Item.h"
#include "Tile.h"

class Block : public Item,
              public Tile
{
public:
    bool isBg = false;

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
    void restore();
    bool hasForegroundBlockAtDistance(int d);

    void onHitBegin();
    void onHitEnd();

protected:
    Block();
    Block(const glm::ivec2 &worldPos);

    int timeSinceLastHit = 0;
    bool beingHit = false;
    int hitSpeed = 300;

    Type type = Type::GOLD;
    State state = State::FULL;

    Texture *texture_full;
    Texture *texture_mid;
    Texture *texture_gone;

    void advanceState();

    virtual void update(int deltaTime) override;
    Texture *getTexture() const override;
};

class BlockGold : public Block
{
public:
    BlockGold(const glm::ivec2 &worldPos = glm::ivec2(0));

private:
    static Texture *s_texture_full;
    static Texture *s_texture_mid;
    static Texture *s_texture_gone;
};

class BlockSapphire : public Block
{
public:
    BlockSapphire(const glm::ivec2 &worldPos = glm::ivec2(0));

private:
    static Texture *s_texture_full;
    static Texture *s_texture_mid;
    static Texture *s_texture_gone;
};

class BlockRuby : public Block
{
public:
    BlockRuby(const glm::ivec2 &worldPos = glm::ivec2(0));

private:
    static Texture *s_texture_full;
    static Texture *s_texture_mid;
    static Texture *s_texture_gone;
};

class BlockEmerald : public Block
{
public:
    BlockEmerald(const glm::ivec2 &worldPos = glm::ivec2(0));

private:
    static Texture *s_texture_full;
    static Texture *s_texture_mid;
    static Texture *s_texture_gone;
};
