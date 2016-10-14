#include "Block.h"

#include "Scene.h"
#include "TileMap.h"

Texture *BlockGold::s_texture_full = NULL;
Texture *BlockGold::s_texture_mid  = NULL;
Texture *BlockGold::s_texture_gone = NULL;
Texture *BlockSapphire::s_texture_full = NULL;
Texture *BlockSapphire::s_texture_mid  = NULL;
Texture *BlockSapphire::s_texture_gone = NULL;
Texture *BlockRuby::s_texture_full = NULL;
Texture *BlockRuby::s_texture_mid  = NULL;
Texture *BlockRuby::s_texture_gone = NULL;
Texture *BlockEmerald::s_texture_full = NULL;
Texture *BlockEmerald::s_texture_mid  = NULL;
Texture *BlockEmerald::s_texture_gone = NULL;

Block::Block()
{
}

Block::~Block()
{
}

Block::Block(const glm::ivec2 &worldPos) : Tile(worldPos)
{
}

void Block::onHitBegin()
{
    beingHit = true;
}

void Block::onHitEnd()
{
    beingHit = false;
    restore();
}

void Block::update(int deltaTime)
{
    if (beingHit)
    {
        timeSinceLastHit += deltaTime;
        if (timeSinceLastHit > hitSpeed && state == FULL)
        {
            advanceState();
        }
        else if (timeSinceLastHit > hitSpeed * 2 && state == MID)
        {
            advanceState();
        }
        else if (timeSinceLastHit > hitSpeed * 3 && state == GONE)
        {
            Inventory *inv = Scene::getPlayer()->getInventory();
            switch (getType())
            {
                case Block::GOLD:     inv->addItem<BlockGold>();     break;
                case Block::SAPPHIRE: inv->addItem<BlockSapphire>(); break;
                case Block::RUBY:     inv->addItem<BlockRuby>();     break;
                case Block::EMERALD:  inv->addItem<BlockEmerald>();  break;
            }
            Scene::getPlayer()->onBlockDeleted(this);
            Scene::getTileMap()->delTile( getPosition() );
        }
    }
}

Block::Type Block::getType() const
{
    return type;
}

void Block::advanceState()
{
    if (state < GONE)
    {
        state = (state == FULL) ? MID : GONE;
    }
}

void Block::restore()
{
    state = FULL;
    timeSinceLastHit = 0;
}

Texture* Block::getTexture() const
{
    switch(state)
    {
        case FULL:
            return texture_full;
        case MID:
            return texture_mid;
        case GONE:
            return texture_gone;
    }
    return NULL;
}


BlockGold::BlockGold(const glm::ivec2 &worldPos) : Block(worldPos)
{
    type = GOLD;

    if (!s_texture_full) {
        s_texture_full = new Texture();
        s_texture_full->loadFromFile("images/goldItemFull.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_mid) {
        s_texture_mid = new Texture();
        s_texture_mid->loadFromFile("images/goldItemMid.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_gone) {
        s_texture_gone = new Texture();
        s_texture_gone->loadFromFile("images/goldItemGone.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    texture_full = BlockGold::s_texture_full;
    texture_mid  = BlockGold::s_texture_mid;
    texture_gone = BlockGold::s_texture_gone;

    itemTexture = texture_full;
}


BlockSapphire::BlockSapphire(const glm::ivec2 &worldPos) : Block(worldPos)
{
    type = SAPPHIRE;

    if (!s_texture_full) {
        s_texture_full = new Texture();
        s_texture_full->loadFromFile("images/sapphireItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_mid) {
        s_texture_mid = new Texture();
        s_texture_mid->loadFromFile("images/sapphireItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_gone) {
        s_texture_gone = new Texture();
        s_texture_gone->loadFromFile("images/sapphireItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    texture_full = BlockSapphire::s_texture_full;
    texture_mid  = BlockSapphire::s_texture_mid;
    texture_gone = BlockSapphire::s_texture_gone;

    itemTexture = texture_full;
}

BlockRuby::BlockRuby(const glm::ivec2 &worldPos) : Block(worldPos)
{
    type = RUBY;

    if (!s_texture_full) {
        s_texture_full = new Texture();
        s_texture_full->loadFromFile("images/rubyItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_mid) {
        s_texture_mid = new Texture();
        s_texture_mid->loadFromFile("images/rubyItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_gone) {
        s_texture_gone = new Texture();
        s_texture_gone->loadFromFile("images/rubyItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    texture_full = BlockRuby::s_texture_full;
    texture_mid  = BlockRuby::s_texture_mid;
    texture_gone = BlockRuby::s_texture_gone;

    itemTexture = texture_full;
}

BlockEmerald::BlockEmerald(const glm::ivec2 &worldPos) : Block(worldPos)
{
    type = EMERALD;

    if (!s_texture_full) {
        s_texture_full = new Texture();
        s_texture_full->loadFromFile("images/emeraldItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_mid) {
        s_texture_mid = new Texture();
        s_texture_mid->loadFromFile("images/emeraldItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_gone) {
        s_texture_gone = new Texture();
        s_texture_gone->loadFromFile("images/emeraldItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    texture_full = BlockEmerald::s_texture_full;
    texture_mid  = BlockEmerald::s_texture_mid;
    texture_gone = BlockEmerald::s_texture_gone;

    itemTexture = texture_full;
}



