#include "Scene.h"
#include "Game.h"

#include <cmath>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "Tile.h"
#include "Block.h"
#include "TileMap.h"


Scene::Scene()
{
}

Scene::~Scene()
{
}

int Scene::getCurrentTime()
{
    return Game::getCurrentScene()->currentTime;
}

ShaderProgram *Scene::getShaderProgram()
{
    return &(Game::getCurrentScene()->texProgram);
}

void Scene::removeSceneNodes()
{
    for (ISceneNode *sceneNode : sceneNodesToBeRemoved)
    {
        sceneNodes.remove(sceneNode);
    }
}

void Scene::init()
{
    initShaders();

    projection = glm::ortho(0.f, float(Game::getScreenWidth() - 1), float(Game::getScreenHeight() - 1), 0.f);
    currentTime = 0.0f;

    for(ISceneNode *sceneNode : sceneNodes)
    {
        sceneNode->init();
    }
}

void Scene::update(int deltaTime)
{
    currentTime += deltaTime;

    for(ISceneNode *sceneNode : sceneNodes)
    {
        sceneNode->update(deltaTime);
    }
    removeSceneNodes();
}

void Scene::_render()
{
    glEnable(GL_TEXTURE_2D);
    texProgram.use();

    texProgram.setUniformMatrix4f("projection", projection);
    texProgram.setUniformMatrix4f("view", glm::mat4(1.0f));
    texProgram.setUniformMatrix4f("model", glm::mat4(1.0f));

    texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
    texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
    texProgram.setUniform2f("windowSize", Game::getScreenWidth(), Game::getScreenHeight());

    renderBackLayer();
    render();

    for(ISceneNode *sceneNode : sceneNodes)
    {
        if (!sceneNode->isScreenNode())
            sceneNode->render(texProgram);
    }

    for(ISceneNode *sceneNode : sceneNodes)
    {
        if (sceneNode->isScreenNode())
            sceneNode->render(texProgram);
    }
}

Text* Scene::createText(const std::string &str, const glm::ivec2 &pos, int size)
{
    Text *t = new Text();
    t->setText(str, size);
    t->setPosition(pos);
    addSceneNode(t);
    return t;
}

void Scene::addSceneNode(ISceneNode *sceneNode)
{
    sceneNodes.push_back(sceneNode);
}

void Scene::removeSceneNode(ISceneNode *sceneNode)
{
    sceneNodesToBeRemoved.push_back(sceneNode);
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
