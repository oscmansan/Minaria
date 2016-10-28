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
}

SceneGame::~SceneGame()
{
    if (map) delete map;
    if (mapBg) delete mapBg;
    if (background) delete background;
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

const std::list<Character *> &SceneGame::getCharacters() const
{
    return characters;
}

void SceneGame::init()
{
    Scene::init();

    // Map init
    background = new Background(texProgram);
    generateProceduralTilemap();

    // Player init
    player = new Player();
    player->init();
    player->setTileMap(map);

    int yPos = mapBg->getSurfaceLevel(player->getPosition().x) - 200;
    glm::ivec2 textPos = glm::ivec2(player->getPosition().x, yPos);

    Text *tutoText1   = createText("Find the              ...", textPos + glm::ivec2(0, 0), 16);
    Text *tutoText1_2 = createText("         golden nugget   ", textPos + glm::ivec2(0, 0), 16);
    tutoText1->setColor(glm::vec4(1,1,1,1));
    tutoText1_2->setColor(glm::vec4(1,1,0,1));
    tutoText1->setIsScreen(false);
    tutoText1_2->setIsScreen(false);

    Text *tutoText2 = createText("To the east!", textPos + glm::ivec2(0, 20), 16);
    tutoText2->setColor(glm::vec4(1,1,1,1));
    tutoText2->setIsScreen(false);

    Text *tutoText3 = createText("GOOD LUCK MINER!", textPos + glm::ivec2(500, 0), 20);
    tutoText3->setColor(glm::vec4(0,0,0,1));
    tutoText3->setIsScreen(false);
    tutoText3->setStroke(4, glm::vec4(1,0.5,0,1));

    // Add to the list of characters
    characters.push_back(player);

    // Enemy init
    int ini = 1500;
    int offset = 300;
    int mapWidth = map->getTotalSizeWorld().x - ini;
    int posx = ini;
    while (posx < mapWidth)
    {
        Enemy *enemy;

        if (rand() % 2 == 0) enemy = new FlyingEnemy(posx); else enemy = new GroundEnemy(posx);
        enemy->init();
        enemy->setTileMap(map);
        characters.push_back(enemy);

        if (offset > 10) offset -= 14;
        posx += offset;
    }

    camera = new Camera();
    camera->init(player->getPosition());

    /*
    SceneGame::getInstance()->addText("0123456789.,", glm::ivec2(0, 0), 16);
    SceneGame::getInstance()->addText("ABCDEFGHIJKLMNOPQRSTUVWXYZ", glm::ivec2(0, 20), 16);
    SceneGame::getInstance()->addText("abcdefghijklmnopqrstuvwxyz", glm::ivec2(0, 40), 16);
    */

    soundManager = new SoundManager();
    soundManager->setVolume(80.f);
    soundManager->playMusic("../sounds/cavesong.ogg");
}

void SceneGame::update(int deltaTime)
{
    if (!gameWon)
    {
        Scene::update(deltaTime);

        camera->update(deltaTime);
        background->update(deltaTime);
        map->update(deltaTime);
        mapBg->update(deltaTime);
    }
    else
    {
        player->winSymbol->update(deltaTime);
    }
}

void SceneGame::renderBackLayer()
{
    Scene::renderBackLayer();
    background->render();
    mapBg->render();
}

void SceneGame::render()
{
    Scene::render();
    map->render();
}

void SceneGame::renderOverlay()
{
    Scene::renderOverlay();
    player->renderHearts(*getShaderProgram());
    if (player->winSymbol) player->winSymbol->render(*getShaderProgram());
}

void SceneGame::winGame()
{
    soundManager->stopMusic();
    soundManager->playMusic("../sounds/FFVI_Victory_Fanfare.ogg");
    gameWon = true;
}

std::list<Character*> SceneGame::whosThere(const glm::ivec2 &pos)
{
    std::list<Character*> result;
    for (Character *c : characters)
    {
        if (c->getBoundingBox().contains(pos))
        {
            result.push_back(c);
        }
    }
    return result;
}

std::list<Character*> SceneGame::whosThereTile(const glm::ivec2 &posWorld)
{
    int tileSize = map->getTileSize();
    Rect tileBoundingRect = Rect(map->worldPosToTilePos(posWorld).x * tileSize,
                                 map->worldPosToTilePos(posWorld).y * tileSize,
                                 tileSize, tileSize);
    std::list<Character*> result;
    for (Character *c : characters)
    {
        if (c->getBoundingBox().intersects(tileBoundingRect))
        {
            result.push_back(c);
        }
    }
    return result;
}

void SceneGame::removeCharacter(Character *character)
{
    characters.remove(character);
}

SoundManager* SceneGame::getSoundManager() {
    return soundManager;
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
            map->addTile<BlockDirt>(pos + glm::ivec2(0, dy));
        }
    }

    // Add mountains using sinus of grounds
    srand(time(0));
    float sinSpeed1 = float(rand()%10)/10.0f + 1.0f;
    float sinSpeed2 = float(rand()%10)/10.0f + 1.0f;
    float sinSpeed3 = float(rand()%10)/10.0f + 1.0f;
    float mountainsAmplitude1 = 2.0f * (rand() % 100) / 100.0f;
    float mountainsAmplitude2 = 2.0f * (rand() % 100) / 100.0f;
    float mountainsAmplitude3 = 2.0f * (rand() % 100) / 100.0f;
    for (int i = 0; i < width; ++i)
    {
        float mountainsFreq = 8;
        float yAngle = (float(i) / width) * 2 * 3.1415926f * mountainsFreq;
        glm::ivec2 pos = glm::ivec2(i * tileSize, groundStartingY);
        pos.y += (glm::sin(yAngle * sinSpeed1) * mountainsAmplitude1) * tileSize;
        pos.y += (glm::cos(yAngle * sinSpeed2) * mountainsAmplitude2) * tileSize;
        pos.y += (glm::sin(yAngle * sinSpeed3) * mountainsAmplitude3) * tileSize;
        pos.y -= 60;

        for (int dy = 0; dy < mapSize.y; dy += tileSize)
        {
            map->addTile<BlockDirt>(pos + glm::ivec2(0,dy));
        }
    }

    for( int i = 0; i < map->getTotalSizeTiles().x; ++i)
    {
        for( int j = 0; j < map->getTotalSizeTiles().y; ++j)
        {
            if (map->getTileAt(glm::ivec2(i,j) * tileSize) != 0)
            {
                mapBg->addTile<BlockDirt>(glm::ivec2(i,j) * tileSize);
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
            const float minRange = -0.015f, maxRange = 0.015f;
            const int octaves = 8;
            float p = 0;
            Tile *t = map->getTileAt(pos);
            Block *b = t ? dynamic_cast<Block*>(t) : NULL;
            if (b && b->getType() == Block::Type::DIRT)
            {
                float perlinx = float(pos.x) / map->getTotalSizeWorld().x * 10.0f;
                float perliny = float(pos.y) / map->getTotalSizeWorld().y * 10.0f;
                p = perlinSapphire.octaveNoise(perlinx, perliny, octaves);
                if (p > minRange * 6.0f && p < maxRange * 6.0f) { map->addTile<BlockRock>(pos); }
                p = perlinRuby.octaveNoise(perlinx, perliny, octaves);
                if (p > minRange && p < maxRange) { map->addTile<BlockPurple>(pos); }
                p = perlinEmerald.octaveNoise(perlinx, perliny, octaves);
                if (p > minRange && p < maxRange) { map->addTile<BlockWood>(pos); }

                float ph = perlinHoles.octaveNoise(perlinx, perliny, octaves);
                if (ph > 0.35f || ph < -0.35f) { map->delTile(pos); }
            }
        }
    }

    // Add gold nugget!
    //glm::ivec2 pos = glm::ivec2(width * tileSize - tileSize * 30, 0);
    //pos.y = map->getSurfaceLevel(pos.x) + tileSize * 4;
    glm::ivec2 pos = glm::ivec2(30 * tileSize, 0);
    pos.y = map->getSurfaceLevel(pos.x) - tileSize * 2;
    map->addTile<BlockGold>(pos);

    // Add side big walls
    for (int x = 25; x >= 0; --x)
    {
        glm::ivec2 pos1 = glm::ivec2(x * tileSize,     0);
        glm::ivec2 pos2 = glm::ivec2(width * tileSize, 0) - pos1;
        for (int y = 0; y < height; ++y)
        {
            map->addTile<BlockBedRock>(pos1 + glm::ivec2(0, y * tileSize)); // Left
            map->addTile<BlockBedRock>(pos2 + glm::ivec2(0, y * tileSize)); // Right
        }
    }
    // Add bedrock ground
    for (int x = 0; x < width; ++x)
    {
        map->addTile<BlockBedRock>(glm::ivec2(x * tileSize, mapSize.y - 1));
    }
}
