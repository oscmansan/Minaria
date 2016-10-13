#ifndef TILE_H
#define TILE_H

#include "Sprite.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include <iostream>
class Tile
{
public:
    Tile();
    Tile(const glm::ivec2 &worldPos);
    virtual ~Tile();

    void render();
    virtual void update(int deltaTime) {}

    Sprite* getSprite() const;
    glm::ivec2 getPosition() const;

protected:

    glm::ivec2 position = glm::ivec2(0,0);

    ShaderProgram *program = NULL;
    Sprite *sprite = NULL;

    virtual Texture *getTexture() const { return NULL; }
};

#endif // TILE_H
