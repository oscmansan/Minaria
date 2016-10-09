#include "Block.h"

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


BlockGold::BlockGold()
{
    type = TYPE_GOLD;
    itemTexture->loadFromFile("images/goldItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

BlockSapphire::BlockSapphire()
{
    type = TYPE_SAPPHIRE;
    itemTexture->loadFromFile("images/sapphireItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

BlockRuby::BlockRuby()
{
    type = TYPE_RUBY;
    itemTexture->loadFromFile("images/rubyItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

BlockEmerald::BlockEmerald()
{
    type = TYPE_EMERALD;
    itemTexture->loadFromFile("images/emeraldItem.png", TEXTURE_PIXEL_FORMAT_RGBA);
}




