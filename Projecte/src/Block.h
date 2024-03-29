#pragma once

#include "Item.h"
#include "Tile.h"

class Block : public Item,
              public Tile
{
public:
    bool isBg = false;
    bool undestroyable = false;
    bool selectedByPlayer = false;

    enum Type
    {
        DIRT    = 1,
        ROCK    = 2,
        BEDROCK = 3,
        WOOD    = 4,
        PURPLE  = 5,
        GOLD = 6
    };

    enum State {
        FULL = 0,
        DEST_1 = 1,
        DEST_2,
        DEST_3,
        DEST_4,
        DEST_5,
        DEST_6,
        DEST_7,
        GONE
    };

    virtual ~Block();

    Type getType() const;
    void restore();
    bool isBorderBlock(int d) const;
    bool hasForegroundBlockAtDistance(int d) const;

    void initBlock();

    void hit(bool mining);
    void onHitBegin();
    void onHitEnd();

protected:
    Block();
    Block(const glm::ivec2 &worldPos);

    int timeSinceLastHit = 0;
    bool beingHit = false;
    int hitSpeed = 300;

    Type type = Type::DIRT;
    State state = State::FULL;

    void advanceState(bool mining);

    virtual void render() override;
    virtual void update(int deltaTime) override;
    int getAnimationFrame() const;
    glm::vec2 getSpriteFrame() const override;
};

class BlockDirt : public Block
{
public:
    BlockDirt(const glm::ivec2 &worldPos = glm::ivec2(0));

private:
    static Texture *s_texture;
};

class BlockRock : public Block
{
public:
    BlockRock(const glm::ivec2 &worldPos = glm::ivec2(0));

private:
    static Texture *s_texture;
};

class BlockBedRock : public Block
{
public:
    BlockBedRock(const glm::ivec2 &worldPos = glm::ivec2(0));

private:
    static Texture *s_texture;
};

class BlockWood : public Block
{
public:
    BlockWood(const glm::ivec2 &worldPos = glm::ivec2(0));

private:
    static Texture *s_texture;
};

class BlockPurple : public Block
{
public:
    BlockPurple(const glm::ivec2 &worldPos = glm::ivec2(0));

public:
    static Texture *s_texture;
};

class BlockGold : public Block
{
public:
    BlockGold(const glm::ivec2 &worldPos = glm::ivec2(0));

private:
    static Texture *s_texture;
};

