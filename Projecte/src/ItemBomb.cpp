#include "ItemBomb.h"

ItemBomb::ItemBomb()
{
    itemTexture = new Texture();
    itemTexture->loadFromFile("images/bomb.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

ItemBomb::~ItemBomb()
{
    delete itemTexture;
}
