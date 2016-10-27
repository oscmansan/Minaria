#include "Bomb.h"

#include "Game.h"
#include "TileMap.h"
#include "BombExplosion.h"

Texture *Bomb::bombTexture = NULL;

Bomb::Bomb()
{
    if (Bomb::bombTexture == NULL)
    {
        Bomb::bombTexture = new Texture();
        Bomb::bombTexture->loadFromFile("images/bomb.png", TEXTURE_PIXEL_FORMAT_RGBA);
        Bomb::bombTexture->setMinFilter(GL_NEAREST);
        Bomb::bombTexture->setMagFilter(GL_NEAREST);
    }

    ShaderProgram *program = Game::getCurrentSceneGame()->getShaderProgram();
    sprite = Sprite::createSprite(glm::ivec2(24), glm::vec2(1.0f), Bomb::bombTexture, program);

    Game::getCurrentScene()->addSceneNode(this);
}

Bomb::~Bomb()
{
    delete sprite;
}

void Bomb::update(int deltaTime)
{
    velocity.x += 0.05f * (velocity.x < 0 ? 1 : -1);
    velocity.x = max(abs(velocity.x), 0.0f) * (velocity.x < 0 ? -1 : 1);
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

    for (Character *c : Game::getCurrentSceneGame()->getCharacters())
    {
        Enemy *e = dynamic_cast<Enemy*>(c);
        if (e)
        {
            Rect eRect = e->getBoundingBox();
            Rect bRect(getPosition().x, getPosition().y,
                       getSize().x, getSize().y);
            if (eRect.intersects(bRect))
            {
                collided = true;
            }
        }
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
    glm::ivec2 centerPos = getPosition() + getSize() / 2;
    Game::getCurrentSceneGame()->getCamera()->tremble(2, 500);

    TileMap *tmap = Game::getCurrentSceneGame()->getTileMap();
    int tileSize = tmap->getTileSize();

    int explosionRadiusInTiles = explosionRadius / tileSize;
    for (int dx = -explosionRadiusInTiles*2; dx <= explosionRadiusInTiles*2; ++dx)
    {
        for (int dy = -explosionRadiusInTiles*2; dy <= explosionRadiusInTiles*2; ++dy)
        {
            glm::ivec2 tilePosWorld = centerPos + (glm::ivec2(dx, dy) * tileSize);
            int dist = abs(tilePosWorld.y - centerPos.y) / tileSize + abs(tilePosWorld.x - centerPos.x) / tileSize;

            int deltaDistance = dist - explosionRadiusInTiles;
            if (deltaDistance <= 0)
            {
                Tile *t = tmap->getTileAt(tilePosWorld);
                Block *b = t ? dynamic_cast<Block*>(t) : NULL;
                if (b)
                {
                    for (int i = 0; i < -deltaDistance * 4; ++i)
                    {
                        b->hit(false);
                    }
                }
            }
        }
    }

    // Collision with enemies
    const std::list<Character*> characters = Game::getCurrentSceneGame()->getCharacters(); // Copy to avoid problems with remove
    for (Character *character : characters)
    {
        if (!character) continue;

        float distToExplosionCenter = glm::distance(glm::vec2(character->getPosition()), glm::vec2(centerPos));
        int damage = damageInCenter * (explosionRadius / (distToExplosionCenter + 0.01f));
        damage = min(damageInCenter, damage);

        if (distToExplosionCenter < explosionRadius)
        {
            Enemy *e = dynamic_cast<Enemy*>(character);
            if (e && !e->dead)
            {
                e->takeDamage(damage);
            }
            else
            {
                Player *p = dynamic_cast<Player*>(character);
                if (p)
                {
                    p->takeDamage(damage);
                }
            }
        }
    }

    BombExplosion *be = new BombExplosion(false);
    be->setPosition(getPosition() + sprite->getSize()/2);
    be->explosionSize = explosionRadius;
    be->init();

    Game::getCurrentScene()->removeSceneNode(this);
}
