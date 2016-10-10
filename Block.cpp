#include "Block.h"

Texture *BlockGold::s_texture_full = NULL;
Texture *BlockGold::s_texture_gone = NULL;
Texture *BlockGold::s_texture_mid  = NULL;
Texture *BlockSapphire::s_texture_full = NULL;
Texture *BlockSapphire::s_texture_gone = NULL;
Texture *BlockRuby::s_texture_mid  = NULL;
Texture *BlockRuby::s_texture_full = NULL;
Texture *BlockRuby::s_texture_gone = NULL;
Texture *BlockEmerald::s_texture_mid  = NULL;
Texture *BlockEmerald::s_texture_full = NULL;
Texture *BlockEmerald::s_texture_gone = NULL;

Block::Block()
{
    itemTexture = new Texture();
    state = FULL;
}

Block::~Block()
{
}

Block::Type Block::getType() const
{
    return type;
}

void Block::hit() {
    if (state < GONE) {
        ++state;
    }
}

void Block::restore() {
    state = FULL;
}

Texture Block::getTexture() {
    switch(state) {
        case FULL:
            return texture_full;
        case MID:
            return texture_mid;
        case GONE:
            return texture_gone;
    }
}


BlockGold::BlockGold()
{
    type = GOLD;
    itemTexture->loadFromFile("images/goldItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
    if (!texture_full) {
        texture_full = new Texture();
        texture_full->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!texture_mid) {
        texture_mid = new Texture();
        texture_mid->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }
    if (!texture_gone) {
        texture_gone = new Texture();
        texture_gone->loadFromFile("", TEXTURE_PIXEL_FORMAT_RGBA);
    }
}

BlockSapphire::BlockSapphire()
{
    type = SAPPHIRE;
    itemTexture->loadFromFile("images/sapphireItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

BlockRuby::BlockRuby()
{
    type = RUBY;
    itemTexture->loadFromFile("images/rubyItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

BlockEmerald::BlockEmerald()
{
    type = EMERALD;
    itemTexture->loadFromFile("images/emeraldItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
}




