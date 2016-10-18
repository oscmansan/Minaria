#include "Block.h"

#define GLM_SWIZZLE

#include "Scene.h"
#include "TileMap.h"

#include <glm/glm.hpp>

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
    //restore();
}

void Block::update(int deltaTime)
{
    if (!isVisible()) return;

    // Lighting
    Player *player = Game::getCurrentSceneGame()->getPlayer();
    float distToPlayer = glm::distance(glm::vec2(getPosition()), glm::vec2(player->getPosition()));
    float fade = (80.0f / (distToPlayer + 0.1f));
    fade = glm::clamp(fade, 0.0f, 1.0f);
    lighting = glm::vec3(fade);

    // Shadow of bg tiles
    if (isBg)
    {
        if (hasForegroundBlockAtDistance(1)) lighting *= 0.5f;
        else if (hasForegroundBlockAtDistance(2)) lighting *= 0.65f;
        else if (hasForegroundBlockAtDistance(3)) lighting *= 0.85f;
    }
    else // Shadow of foreground tiles
    {
        /*
        if (isBorderBlock(1))
        {
            lighting *= 1.0f;
        }
        else if (isBorderBlock(2))
        {
            lighting *= 0.6f;
        }
        else
        {
            lighting *= 0.3f;
        }
        */
    }

    // States
    if (beingHit)
    {
        timeSinceLastHit += deltaTime;
        if (/*timeSinceLastHit > hitSpeed &&*/state == FULL)
        {
            advanceState();
        }
        else if (timeSinceLastHit > hitSpeed * 2 && state == MID)
        {
            advanceState();
        }
        else if (timeSinceLastHit > hitSpeed * 3 && state == GONE)
        {
            advanceState();
        }
    }
}

Block::Type Block::getType() const
{
    return type;
}

void Block::advanceState()
{
    Player *player = Game::getCurrentSceneGame()->getPlayer();
    if (state == GONE)
    {
        Inventory *inv = player->getInventory();
        switch (getType())
        {
            case Block::GOLD:     inv->addItem<BlockGold>();     break;
            case Block::SAPPHIRE: inv->addItem<BlockSapphire>(); break;
            case Block::RUBY:     inv->addItem<BlockRuby>();     break;
            case Block::EMERALD:  inv->addItem<BlockEmerald>();  break;
        }
        player->onBlockDeleted(this);
        Game::getCurrentSceneGame()->getTileMap()->delTile( getPosition() );
    }
    else
    {
        state = (state == FULL) ? MID : GONE;
    }
}

void Block::restore()
{
    state = FULL;
    timeSinceLastHit = 0;
}

bool Block::isBorderBlock(int d) const
{
    TileMap *foreground = Game::getCurrentSceneGame()->getTileMap();
    glm::ivec2 step = glm::ivec2(foreground->getTileSize());
    glm::ivec2 pos = getPosition();
    return foreground->getTileAt(pos + d * glm::ivec2( step.x, 0)) == NULL ||
           foreground->getTileAt(pos + d * glm::ivec2(-step.x, 0)) == NULL ||
           foreground->getTileAt(pos + d * glm::ivec2(0,  step.y)) == NULL ||
           foreground->getTileAt(pos + d * glm::ivec2(0, -step.y)) == NULL ||
           foreground->getTileAt(pos + d * glm::ivec2(-step.x, -step.y)) == NULL ||
           foreground->getTileAt(pos + d * glm::ivec2(-step.x,  step.y)) == NULL ||
           foreground->getTileAt(pos + d * glm::ivec2( step.x, -step.y)) == NULL ||
           foreground->getTileAt(pos + d * glm::ivec2( step.x,  step.y)) == NULL;
}

bool Block::hasForegroundBlockAtDistance(int d) const
{
    TileMap *foreground = Game::getCurrentSceneGame()->getTileMap();
    glm::ivec2 step = glm::ivec2(foreground->getTileSize());
    glm::ivec2 pos = getPosition();
    return foreground->getTileAt(pos + d * glm::ivec2( step.x, 0)) != NULL ||
           foreground->getTileAt(pos + d * glm::ivec2(-step.x, 0)) != NULL ||
           foreground->getTileAt(pos + d * glm::ivec2(0,  step.y)) != NULL ||
           foreground->getTileAt(pos + d * glm::ivec2(0, -step.y)) != NULL ||
           foreground->getTileAt(pos + d * glm::ivec2(-step.x, -step.y)) != NULL ||
           foreground->getTileAt(pos + d * glm::ivec2(-step.x,  step.y)) != NULL ||
           foreground->getTileAt(pos + d * glm::ivec2( step.x, -step.y)) != NULL ||
            foreground->getTileAt(pos + d * glm::ivec2( step.x,  step.y)) != NULL;
}

void Block::hit()
{
    advanceState();
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



