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
	int width = 108;
	int height = 28;
	map = TileMap::createTileMap(glm::ivec2(width, height), texProgram);

	int tileSize = map->getTileSize();
	glm::ivec2 mapSize = map->getTotalSizeWorld();

	// Add flat ground
	for (int i = 0; i < width; ++i)
	{
		glm::ivec2 pos = glm::ivec2(i * tileSize, (height - 1) * tileSize);
		map->addTile(pos, 1);
	}

	// Add sinus ground
	for (int i = 0; i < width; ++i)
	{
		float mountainsFreq = 5;
		float mountainsAmplitude = 5;
		float yAngle = (float(i) / width) * 2 * 3.1415926f * mountainsFreq;
		glm::ivec2 pos = glm::ivec2(i * tileSize, 
									((height - 1) - (glm::sin(yAngle) * mountainsAmplitude + 10)) * tileSize);
		map->addTile(pos, 1);
	}
}

