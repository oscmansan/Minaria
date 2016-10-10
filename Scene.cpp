#include "Scene.h"
#include "Game.h"

#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

Scene* Scene::singleton = NULL;

Scene::Scene()
{
	map = NULL;
	player = NULL;
	camera = NULL;

    Scene::singleton = this;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}

Scene *Scene::getInstance()
{
	return Scene::singleton;
}

int Scene::getCurrentTime()
{
	return Scene::getInstance()->currentTime;
}

Player *Scene::getPlayer()
{
	return Scene::getInstance()->player;
}

Camera *Scene::getCamera()
{
	return Scene::getInstance()->camera;
}

TileMap *Scene::getTileMap() {
	return Scene::getInstance()->map;
}

void Scene::init()
{
	initShaders();
	//map = TileMap::createTileMap("levels/level02.txt", texProgram);
	generateProceduralTilemap(); 

    textureBg.loadFromFile("images/background.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteBg = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.0f),
                                    &textureBg, &texProgram);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	// Player init
	player = new Player();
	player->init(texProgram);
	player->setTileMap(map);

	// Enemy init
	for (int i = 0; i < 10; ++i)
	{
		Enemy *enemy = new Enemy();
		enemy->init(texProgram);
		enemy->setPosition(enemy->getPosition() + glm::ivec2(i * 60, -i * 60));
		enemy->setTileMap(map);
		characters.push_back(enemy);
	}
	
	camera = new Camera();
    camera->init(player->getPosition());

	// Add to the list of characters
	characters.push_back(player);
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	for (Character *character : characters)
	{
		character->update(deltaTime);
	}

	camera->update();
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();

    texProgram.setUniformMatrix4f("projection", projection);
    texProgram.setUniformMatrix4f("model", glm::mat4(1.0f));
    spriteBg->render();

	glm::mat4 view = camera->getView();
	texProgram.setUniformMatrix4f("view", view);
	texProgram.setUniformMatrix4f("model", glm::mat4(1.0f));

	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	map->render();

	for (Character *character : characters)
	{
		character->render(texProgram);
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

Character* Scene::whosThere(const glm::ivec2 &pos) {
	for (Character *c : characters) {
		if (c->getBoundingBox().contains(pos)) {
			return c;
		}
	}
	return NULL;
}

void Scene::generateProceduralTilemap()
{
    int width = 256;
    int height = 128;
	map = TileMap::createTileMap(glm::ivec2(width, height), texProgram);

	int tileSize = map->getTileSize();
	glm::ivec2 mapSize = map->getTotalSizeWorld();

    int groundStartingY = 2000;
	// Add flat ground
    for (int x = 0; x < width; ++x)
	{
        glm::ivec2 pos = glm::ivec2(x * tileSize, groundStartingY);
        for (int dy = 0; dy < SCREEN_HEIGHT; dy += tileSize)
        {
            map->addTile(pos + glm::ivec2(0, dy), 1, false);
        }
	}

    // Add mountains using sinus of grounds
    srand(time(0));
    float sinSpeed1 = float(rand()%10)/10.0f + 0.5f;
    float sinSpeed2 = float(rand()%10)/10.0f + 0.5f;
    float sinSpeed3 = float(rand()%10)/10.0f + 0.5f;
	for (int i = 0; i < width; ++i)
	{
		float mountainsFreq = 5;
		float mountainsAmplitude = 5;
		float yAngle = (float(i) / width) * 2 * 3.1415926f * mountainsFreq;
        glm::ivec2 pos = glm::ivec2(i * tileSize, groundStartingY);
        pos.y += (glm::sin(yAngle * sinSpeed1) * mountainsAmplitude * 0.6f - 10) * tileSize;
        pos.y += (glm::cos(yAngle * sinSpeed2) * mountainsAmplitude * 0.4f - 10) * tileSize;
        pos.y += (glm::sin(yAngle * sinSpeed3) * mountainsAmplitude * 0.4f - 10) * tileSize;

        for (int dy = 0; dy < SCREEN_HEIGHT; dy += tileSize)
        {
            map->addTile(pos + glm::ivec2(0,dy), 1, false);
        }
	}

    // Add side big walls
    for (int x = 25; x >= 0; --x)
    {
        glm::ivec2 pos1 = glm::ivec2(x * tileSize,     0);
        glm::ivec2 pos2 = glm::ivec2(width * tileSize, 0) - pos1;
        for (int y = 0; y < height; ++y)
        {
            map->addTile(pos1 + glm::ivec2(0, y * tileSize), 1, false); // Left
            map->addTile(pos2 + glm::ivec2(0, y * tileSize), 1, false); // Right
        }
    }

    const int NumMineralPotatoes = 300;
    for (int i = 0; i < NumMineralPotatoes; ++i)
    {
        addTerrainPotato();
    }

    map->updateVAO();
}

void Scene::addTerrainPotato()
{
    int blockType = rand() % 3 + 2;
    glm::ivec2 center;
    int tileSize = map->getTileSize();
    while (true)
    {
        center = glm::ivec2(rand() % map->getTotalSizeWorld().x,
                            rand() % map->getTotalSizeWorld().y);

        // Find the center of the tile in a terrain
        if (map->getTileAt(center) == 1)
        {
            // Add potato, with decreasing probability around its center
            for (int dy = -2; rand() % int(max(1.0, abs(dy * 1.5 + 1))) == 0; ++dy)
            {
                for (int dx = -2; rand() % int(max(1.0, abs(dx * 1.5 + 1))) == 0; ++dx)
                {
                    glm::ivec2 newPos = center + glm::ivec2(dx,dy) * tileSize;
                    if (map->getTileAt(newPos) == 1)
                    {
                        map->addTile(newPos, blockType, false);
                    }
                }
            }
            break;
        }
    }
}

