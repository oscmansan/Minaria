#include "Tile.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"
#include "Scene.h"
#include "TileMap.h"

Texture *Tile::defaultTexture = NULL;

Tile::Tile()
{
    if (!Tile::defaultTexture)
    {
        Tile::defaultTexture = new Texture();
    }

    program = Scene::getShaderProgram();
    int tileSize = Game::getCurrentSceneGame()->getTileMap()->getTileSize();
    sprite = Sprite::createSprite(glm::ivec2(tileSize), glm::vec2(1.0f), Tile::defaultTexture, program);
}

Tile::Tile(const glm::ivec2 &worldPos) : Tile()
{
    position = worldPos;
}

Tile::~Tile()
{
    delete sprite;
}

void Tile::render()
{
    prepareModelViewMatrix();

    glm::vec4 tint = sprite->getTint();
    sprite->changeAnimation( getAnimationFrame() );
    sprite->setTint( glm::vec4(lighting * glm::vec3(tint.x, tint.y, tint.z), tint.w) );
    sprite->render();
}

Sprite *Tile::getSprite() const
{
    return sprite;
}

bool Tile::isVisible() const
{
    const glm::mat4 &view = Game::getCurrentSceneGame()->getCamera()->getView();

    int offset = 32;
    Rect screenRect = Rect(-offset, -offset, Game::getScreenWidth() + offset, Game::getScreenHeight() + offset);
    glm::vec4 v4 = (view * glm::vec4(getPosition(), 0, 1));
    return screenRect.contains( glm::ivec2(v4.x, v4.y) );
}
