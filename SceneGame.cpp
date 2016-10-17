#include "SceneGame.h"
#include "Game.h"

#include <cmath>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "Tile.h"
#include "Block.h"
#include "TileMap.h"
#include "Background.h"

SceneGame::SceneGame()
{
    map = NULL;
    player = NULL;
    camera = NULL;
}

SceneGame::~SceneGame()
{
    if(map != NULL)
        delete map;
    if(mapBg != NULL)
        delete mapBg;
    if (player != NULL)
        delete player;
}

Player *SceneGame::getPlayer() const
{
    return player;
}

Camera *SceneGame::getCamera() const
{
    return camera;
}

TileMap *SceneGame::getTileMap() const
{
    return map;
}

void SceneGame::init()
{
    Scene::init();

    // Map init
    background = new Background(texProgram);
    generateProceduralTilemap();

    // Player init
    player = new Player();
    player->init(texProgram);
    player->setTileMap(map);

    // Add to the list of characters
    characters.push_back(player);

    // Enemy init
    /*for (int i = 0; i < 10; ++i)
    {
        Enemy *enemy = new Enemy();
        enemy->init(texProgram);
        enemy->setPosition(enemy->getPosition() + glm::ivec2(i * 60, -i * 60));
        enemy->setTileMap(map);
        characters.push_back(enemy);
    }
    */

    camera = new Camera();
    camera->init(player->getPosition());

    /*
    SceneGame::getInstance()->addText("0123456789.,", glm::ivec2(0, 0), 16);
    SceneGame::getInstance()->addText("ABCDEFGHIJKLMNOPQRSTUVWXYZ", glm::ivec2(0, 20), 16);
    SceneGame::getInstance()->addText("abcdefghijklmnopqrstuvwxyz", glm::ivec2(0, 40), 16);
    */
}

void SceneGame::update(int deltaTime)
{
    Scene::update(deltaTime);

    currentTime += deltaTime;
    for (Character *character : characters)
    {
        character->update(deltaTime);
    }

    camera->update();
    background->update(deltaTime);
    map->update(deltaTime);
}

void SceneGame::render()
{
    background->render();

    glm::mat4 view = camera->getView();
    texProgram.setUniformMatrix4f("view", view);

    mapBg->render();
    map->render();

    for (Character *character : characters)
    {
        character->render(texProgram);
    }
}

Character* SceneGame::whosThere(const glm::ivec2 &pos)
{
    for (Character *c : characters)
    {
        if (c->getBoundingBox().contains(pos))
        {
            return c;
        }
    }
    return NULL;
}

void SceneGame::generateProceduralTilemap()
{
    int width = 256;
    int height = 128;
    map   = TileMap::createTileMap(glm::ivec2(width, height), texProgram);
    mapBg = TileMap::createTileMap(glm::ivec2(width, height), texProgram);
    mapBg->isBg = true;

    int tileSize = map->getTileSize();
    glm::ivec2 mapSize = map->getTotalSizeWorld();

    int groundStartingY = (height - height/4) * tileSize;
    // Add flat ground
    for (int x = 0; x < width; ++x)
    {
        glm::ivec2 pos = glm::ivec2(x * tileSize, groundStartingY);
        for (int dy = 0; dy <= groundStartingY; dy += tileSize)
        {
            map->addTile<BlockGold>(pos + glm::ivec2(0, dy));
        }
    }

    // Add mountains using sinus of grounds
    srand(time(0));
    float sinSpeed1 = float(rand()%10)/10.0f + 1.0f;
    float sinSpeed2 = float(rand()%10)/10.0f + 1.0f;
    float sinSpeed3 = float(rand()%10)/10.0f + 1.0f;
    for (int i = 0; i < width; ++i)
    {
        float mountainsFreq = 8;
        float mountainsAmplitude = 2.0f;
        float yAngle = (float(i) / width) * 2 * 3.1415926f * mountainsFreq;
        glm::ivec2 pos = glm::ivec2(i * tileSize, groundStartingY);
        pos.y += (glm::sin(yAngle * sinSpeed1) * mountainsAmplitude) * tileSize;
        pos.y += (glm::cos(yAngle * sinSpeed2) * mountainsAmplitude) * tileSize;
        pos.y += (glm::sin(yAngle * sinSpeed3) * mountainsAmplitude) * tileSize;
        pos.y -= 60;

        for (int dy = 0; dy < mapSize.y; dy += tileSize)
        {
            map->addTile<BlockGold>(pos + glm::ivec2(0,dy));
        }
    }

    for( int i = 0; i < map->getTotalSizeTiles().x; ++i)
    {
        for( int j = 0; j < map->getTotalSizeTiles().y; ++j)
        {
            if (map->getTileAt(glm::ivec2(i,j) * tileSize) != 0)
            {
                Tile *t = mapBg->addTile<BlockGold>(glm::ivec2(i,j) * tileSize);
                if (t)
                {
                    float bgTint = 0.4f;
                    t->getSprite()->setTint( glm::vec4(0, 0, 0, bgTint) );
                }
            }
        }
    }

    // Add minerals and holes
    PerlinNoise perlinSapphire(time(0) * rand()),
                perlinRuby(time(0) * rand()),
                perlinEmerald(time(0) * rand()),
                perlinHoles(time(0) * rand());
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            glm::ivec2 pos = glm::ivec2(x,y) * tileSize;
            const float minRange = 0.0f, maxRange = 0.03f;
            const int octaves = 8;
            float p = 0;
            Tile *t = map->getTileAt(pos);
            Block *b = t ? dynamic_cast<Block*>(t) : NULL;
            if (b && b->getType() == Block::Type::GOLD)
            {
                float perlinx = float(pos.x) / map->getTotalSizeWorld().x * 10.0f;
                float perliny = float(pos.y) / map->getTotalSizeWorld().y * 10.0f;
                p = perlinSapphire.octaveNoise(perlinx, perliny, octaves);
                if (p > minRange && p < maxRange) { map->addTile<BlockSapphire>(pos); }
                p = perlinRuby.octaveNoise(perlinx, perliny, octaves);
                if (p > minRange && p < maxRange) { map->addTile<BlockRuby>(pos); }
                p = perlinEmerald.octaveNoise(perlinx, perliny, octaves);
                if (p > minRange && p < maxRange) { map->addTile<BlockEmerald>(pos); }

                float ph = perlinHoles.octaveNoise(perlinx, perliny, octaves);
                if (ph > 0.35f || ph < -0.35f) { map->delTile(pos); }
            }
        }
    }

    // Add side big walls
    for (int x = 25; x >= 0; --x)
    {
        glm::ivec2 pos1 = glm::ivec2(x * tileSize,     0);
        glm::ivec2 pos2 = glm::ivec2(width * tileSize, 0) - pos1;
        for (int y = 0; y < height; ++y)
        {
            map->addTile<BlockGold>(pos1 + glm::ivec2(0, y * tileSize)); // Left
            map->addTile<BlockGold>(pos2 + glm::ivec2(0, y * tileSize)); // Right
        }
    }
}
