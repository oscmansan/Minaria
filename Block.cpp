#include "Block.h"

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
    itemTexture = new Texture();
}

Block::~Block()
{
}

Block::Type Block::getType() const
{
    return type;
}

void Block::hit()
{
    if (state < GONE)
    {
        state = (state == FULL) ? MID : GONE;
    }
}

void Block::restore()
{
    state = FULL;
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
    return nullptr;
}


BlockGold::BlockGold()
{
    type = GOLD;
    itemTexture->loadFromFile("images/goldItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    if (!s_texture_full) {
        s_texture_full = new Texture();
        s_texture_full->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_mid) {
        s_texture_mid = new Texture();
        s_texture_mid->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_gone) {
        s_texture_gone = new Texture();
        s_texture_gone->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    texture_full = BlockGold::s_texture_full;
    texture_mid  = BlockGold::s_texture_mid;
    texture_gone = BlockGold::s_texture_gone;
}

BlockSapphire::BlockSapphire()
{
    type = SAPPHIRE;
    itemTexture->loadFromFile("images/sapphireItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    if (!s_texture_full) {
        s_texture_full = new Texture();
        s_texture_full->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_mid) {
        s_texture_mid = new Texture();
        s_texture_mid->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_gone) {
        s_texture_gone = new Texture();
        s_texture_gone->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    texture_full = BlockSapphire::s_texture_full;
    texture_mid  = BlockSapphire::s_texture_mid;
    texture_gone = BlockSapphire::s_texture_gone;
}

BlockRuby::BlockRuby()
{
    type = RUBY;
    itemTexture->loadFromFile("images/rubyItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    if (!s_texture_full) {
        s_texture_full = new Texture();
        s_texture_full->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_mid) {
        s_texture_mid = new Texture();
        s_texture_mid->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_gone) {
        s_texture_gone = new Texture();
        s_texture_gone->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    texture_full = BlockRuby::s_texture_full;
    texture_mid  = BlockRuby::s_texture_mid;
    texture_gone = BlockRuby::s_texture_gone;
}

BlockEmerald::BlockEmerald()
{
    type = EMERALD;
    itemTexture->loadFromFile("images/emeraldItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    if (!s_texture_full) {
        s_texture_full = new Texture();
        s_texture_full->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_mid) {
        s_texture_mid = new Texture();
        s_texture_mid->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!s_texture_gone) {
        s_texture_gone = new Texture();
        s_texture_gone->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    texture_full = BlockEmerald::s_texture_full;
    texture_mid  = BlockEmerald::s_texture_mid;
    texture_gone = BlockEmerald::s_texture_gone;
}




