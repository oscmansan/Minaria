#include "Block.h"

#define GLM_SWIZZLE

#include "Scene.h"
#include "TileMap.h"

#include <glm/glm.hpp>

Texture *BlockDirt::s_texture    = NULL;
Texture *BlockRock::s_texture    = NULL;
Texture *BlockBedRock::s_texture = NULL;
Texture *BlockWood::s_texture    = NULL;
Texture *BlockPurple::s_texture  = NULL;

Block::Block() : Tile(), Item()
{
    initBlock();
}

Block::~Block()
{
}

void Block::initBlock()
{
    if (sprite) delete sprite;

    int tileSize = Game::getCurrentSceneGame()->getTileMap()->getTileSize();
    sprite = Sprite::createSprite(glm::ivec2(tileSize), glm::vec2(1.0f / 8.0f, 1.0f), Tile::defaultTexture, program);
    sprite->setNumberAnimations(GONE - 1);

    float xDisplacement = 1.0f / 8.0f;
    sprite->addKeyframe(FULL,   float(FULL  ) * glm::vec2(xDisplacement, 0.0f));
    sprite->addKeyframe(DEST_1, float(DEST_1) * glm::vec2(xDisplacement, 0.0f));
    sprite->addKeyframe(DEST_2, float(DEST_2) * glm::vec2(xDisplacement, 0.0f));
    sprite->addKeyframe(DEST_3, float(DEST_3) * glm::vec2(xDisplacement, 0.0f));
    sprite->addKeyframe(DEST_4, float(DEST_4) * glm::vec2(xDisplacement, 0.0f));
    sprite->addKeyframe(DEST_5, float(DEST_5) * glm::vec2(xDisplacement, 0.0f));
    sprite->addKeyframe(DEST_6, float(DEST_6) * glm::vec2(xDisplacement, 0.0f));
    sprite->addKeyframe(DEST_7, float(DEST_7) * glm::vec2(xDisplacement, 0.0f));
    sprite->addKeyframe(GONE,   float(GONE  ) * glm::vec2(xDisplacement, 0.0f));
}

Block::Block(const glm::ivec2 &worldPos) : Tile(worldPos)
{
    initBlock();
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
    fade *= fade;
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
            lighting *= 0.5f;
        }
        else if (isBorderBlock(3))
        {
            lighting *= 0.3f;
        }
        else
        {
            lighting *= 0.0f;
        }
        */
    }

    // States
    if (beingHit)
    {
        timeSinceLastHit += deltaTime;
        if (timeSinceLastHit > hitSpeed)
        {
            advanceState(true);
            timeSinceLastHit = 0;
        }
    }
}

int Block::getAnimationFrame() const
{
    return static_cast<int>(state);
}

glm::vec2 Block::getSpriteFrame() const
{
    return glm::vec2(1.0f / 8.0f, 1.0f);
}

Block::Type Block::getType() const
{
    return type;
}

void Block::advanceState(bool mining)
{
    if (undestroyable) return;

    Player *player = Game::getCurrentSceneGame()->getPlayer();
    if (state == DEST_7 and mining)
    {
        Inventory *inv = player->getInventory();
        switch (getType())
        {
            case Block::DIRT:    inv->addItem<BlockDirt>();    break;
            case Block::ROCK:    inv->addItem<BlockRock>();    break;
            case Block::BEDROCK: inv->addItem<BlockBedRock>(); break;
            case Block::WOOD:    inv->addItem<BlockWood>();    break;
            case Block::PURPLE:    inv->addItem<BlockWood>();    break;
        }
        player->onBlockDeleted(this);
        Game::getCurrentSceneGame()->getTileMap()->delTile( getPosition() );
    }
    else
    {
        if (state == FULL)        state = DEST_1;
        else if (state == DEST_1) state = DEST_2;
        else if (state == DEST_2) state = DEST_3;
        else if (state == DEST_3) state = DEST_4;
        else if (state == DEST_4) state = DEST_5;
        else if (state == DEST_5) state = DEST_6;
        else if (state == DEST_6) state = DEST_7;
        else if (state == DEST_7) state = GONE;
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

void Block::hit(bool mining)
{
    advanceState(mining);
}


BlockDirt::BlockDirt(const glm::ivec2 &worldPos) : Block(worldPos)
{
    hitSpeed = 80;
    type = DIRT;

    if (!s_texture)
    {
        s_texture = new Texture();
        s_texture->loadFromFile("images/dirt.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    sprite->setTexture(s_texture);

    itemTexture = s_texture;
}


BlockRock::BlockRock(const glm::ivec2 &worldPos) : Block(worldPos)
{
    hitSpeed = 300;
    type = ROCK;

    if (!s_texture)
    {
        s_texture = new Texture();
        s_texture->loadFromFile("images/rock.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    sprite->setTexture(s_texture);

    itemTexture = s_texture;
}

BlockBedRock::BlockBedRock(const glm::ivec2 &worldPos) : Block(worldPos)
{
    hitSpeed = 9999999;
    type = BEDROCK;
    undestroyable = true;

    if (!s_texture)
    {
        s_texture = new Texture();
        s_texture->loadFromFile("images/bedRock.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    sprite->setTexture(s_texture);

    itemTexture = s_texture;
}

BlockWood::BlockWood(const glm::ivec2 &worldPos) : Block(worldPos)
{
    hitSpeed = 400;
    type = WOOD;

    if (!s_texture)
    {
        s_texture = new Texture();
        s_texture->loadFromFile("images/wood.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    sprite->setTexture(s_texture);

    itemTexture = s_texture;
}

BlockPurple::BlockPurple(const glm::ivec2 &worldPos) : Block(worldPos)
{
    hitSpeed = 500;
    type = PURPLE;

    if (!s_texture)
    {
        s_texture = new Texture();
        s_texture->loadFromFile("images/purple.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    sprite->setTexture(s_texture);

    itemTexture = s_texture;
}






