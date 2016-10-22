#include "ItemPickaxe.h"

ItemPickaxe::ItemPickaxe()
{
    itemTexture = new Texture();
    itemTexture->loadFromFile("images/pickaxe.png", TEXTURE_PIXEL_FORMAT_RGBA);
}
