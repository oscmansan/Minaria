#include "Tile.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"
#include "Scene.h"

Texture *Tile::defaultTexture = NULL;

Tile::Tile()
{
    if (!Tile::defaultTexture)
    {
        Tile::defaultTexture = new Texture();
    }

    program = Scene::getShaderProgram();
    sprite = Sprite::createSprite(glm::ivec2(24), glm::vec2(1.0f), Tile::defaultTexture, program);
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

    glm::vec4 tint = sprite->getTint();
    sprite->setTint( glm::vec4(lighting * glm::vec3(tint.x, tint.y, tint.z), tint.w) );
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

bool Tile::isVisible() const
{
    const glm::mat4 &view = Game::getCurrentSceneGame()->getCamera()->getView();

    int offset = 32;
    Rect screenRect = Rect(-offset, -offset, SCREEN_WIDTH + offset, SCREEN_HEIGHT + offset);
    glm::vec4 v4 = (view * glm::vec4(getPosition(), 0, 1));
    return screenRect.contains( glm::ivec2(v4.x, v4.y) );
}
