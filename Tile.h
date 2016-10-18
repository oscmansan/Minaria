#ifndef TILE_H
#define TILE_H

#include <iostream>

#include "Sprite.h"
#include "Texture.h"
#include "ISceneNode.h"
#include "ShaderProgram.h"

class Tile : public ISceneNode
{
public:
    Tile();
    Tile(const glm::ivec2 &worldPos);
    virtual ~Tile();

    void render();
    virtual void update(int deltaTime) {}

    Sprite* getSprite() const;

    bool isVisible() const;

protected:
    static Texture *defaultTexture;

    glm::vec3 lighting = glm::vec3(1.0f);

    ShaderProgram *program = NULL;
    Sprite *sprite = NULL;

    virtual Texture *getTexture() const { return NULL; }
};

#endif // TILE_H
