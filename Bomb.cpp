#include "Bomb.h"

#include "Game.h"
#include "TileMap.h"

Texture *Bomb::bombTexture = NULL;

Bomb::Bomb()
{
    if (Bomb::bombTexture == NULL)
    {
        Bomb::bombTexture = new Texture();
        Bomb::bombTexture->loadFromFile("images/bomb.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }

    ShaderProgram *program = Game::getCurrentSceneGame()->getShaderProgram();
    sprite = Sprite::createSprite(glm::ivec2(24), glm::vec2(1.0f), Bomb::bombTexture, program);

    Game::getCurrentScene()->addSceneNode(this);
}

Bomb::~Bomb()
{
    std::cout << "DELETE CALLED" << std::endl;
    delete sprite;
}

void Bomb::update(int deltaTime)
{
    velocity.x *= 0.99f;
    velocity.y += 0.3f; // Gravity
    velocity.y = min(3.0f, velocity.y);

    setPosition( getPosition() + glm::ivec2(velocity) );
    rotation += rotSpeed * velocity.x * velocity.y;

    bool collided = false;
    TileMap *tmap = Game::getCurrentSceneGame()->getTileMap();
    if (tmap->collisionMoveLeft(position, sprite->getSize()))
    {
        position.x -= velocity.x;
        velocity.x = 0.0f;
        collided = true;
    }

    if (tmap->collisionMoveRight(position, sprite->getSize()))
    {
        position.x -= velocity.x;
        velocity.x = 0.0f;
        collided = true;
    }

    if (tmap->collisionMoveDown(position, sprite->getSize(), &position.y))
    {
        velocity.y = 0.0f;
        collided = true;
    }

    if (tmap->collisionMoveUp(position, sprite->getSize(), &position.y))
    {
        velocity.y = 0.0f;
        collided = true;
    }

    if (collided)
    {
        explode();
    }
}

void Bomb::render(ShaderProgram &program)
{
    prepareModelViewMatrix();
    sprite->render();
}

void Bomb::setVelocity(const glm::vec2 &vel)
{
    velocity = vel;
}

glm::ivec2 Bomb::getSize() const
{
    return sprite ? sprite->getSize() : glm::ivec2(0,0);
}

void Bomb::explode()
{
    TileMap *tmap = Game::getCurrentSceneGame()->getTileMap();
    int tileSize = tmap->getTileSize();
    glm::ivec2 pos = getPosition() + sprite->getSize();
    for (int dx = -explosionRadius*2; dx <= explosionRadius*2; ++dx)
    {
        for (int dy = -explosionRadius*2; dy <= explosionRadius*2; ++dy)
        {
            glm::ivec2 tilePosWorld = pos + (glm::ivec2(dx, dy) * tileSize);

            Tile *t = tmap->getTileAt(tilePosWorld);
            Block *b = t ? dynamic_cast<Block*>(t) : NULL;
            if (b)
            {
                int dist = abs(tilePosWorld.y - pos.y) / tileSize + abs(tilePosWorld.x - pos.x) / tileSize;
                if (dist <= explosionRadius) { b->hit(); b->hit(); b->hit(); }
                else if (dist == explosionRadius + 1) { b->hit(); b->hit(); }
                else if (dist == explosionRadius + 2) { b->hit(); }
            }
        }
    }

    Game::getCurrentScene()->removeSceneNode(this);
}
