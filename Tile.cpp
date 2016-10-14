#include "Tile.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"

Texture *Tile::defaultTexture = NULL;

Tile::Tile()
{
    if (!Tile::defaultTexture)
    {
        Tile::defaultTexture = new Texture();
    }

    program = Scene::getShaderProgram();
    sprite = Sprite::createSprite(glm::ivec2(32), glm::vec2(1.0f), Tile::defaultTexture, program);
}

Tile::Tile(const glm::ivec2 &worldPos) : Tile()
{
    position = worldPos;
}

Tile::~Tile()
{
}

void Tile::render()
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.f));
    program->setUniformMatrix4f("model", model);
    sprite->setTexture(getTexture());
    sprite->render();
}

Sprite *Tile::getSprite() const
{
    return sprite;
}

glm::ivec2 Tile::getPosition() const
{
    return position;
}
