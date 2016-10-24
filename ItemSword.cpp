#include "ItemSword.h"

ItemSword::ItemSword()
{
    itemTexture = new Texture();
    itemTexture->loadFromFile("images/sword.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

ItemSword::~ItemSword()
{
    delete itemTexture;
}
