#include <GL/glew.h>
#include <GL/glut.h>

#include "Game.h"
#include "Scene.h"
#include "Camera.h"

void Game::init()
{
    bPlay = true;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    gotoSceneGame();
    soundManager = new SoundManager();
    soundManager->playMusic("../sounds/hack_the_forest.ogg");
}

bool Game::update(int deltaTime)
{
    if (nextScene) // Change scene
    {
        if (currentScene) delete currentScene;
        currentScene = nextScene;
        currentScene->init();
        nextScene = NULL;
    }

    currentScene->update(deltaTime);
    for (int i = 0; i < 256; ++i) { keysLast[i] = keys[i]; }
    for (int i = 0; i < 256; ++i) { specialKeysLast[i] = specialKeys[i]; }
    mouseLeftButtonLast  = mouseLeftButton;
    mouseRightButtonLast = mouseRightButton;
	return bPlay;
}

Scene *Game::getCurrentScene()
{
    return Game::instance().currentScene;
}

SceneGame *Game::getCurrentSceneGame()
{
    return dynamic_cast<SceneGame*>(Game::instance().currentScene);
}

int Game::getScreenWidth()
{
    return Game::instance().InitialWidth;
}

int Game::getScreenHeight()
{
    return Game::instance().InitialHeight;
}

void Game::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (currentScene)
    {
        currentScene->_render();
    }
}

void Game::gotoSceneMenu()
{
    nextScene = new SceneMenu();
}

void Game::gotoSceneGame()
{
    nextScene = new SceneGame();
}

void Game::gotoSceneCredits()
{
    nextScene = new SceneCredits();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	mousePos = glm::ivec2(x, y);
}

void Game::mousePress(int button)
{
    mouseLeftButton  = mouseLeftButton  || (button == 0);
    mouseRightButton = mouseRightButton || (button == 2);
}

void Game::mouseRelease(int button)
{
    mouseLeftButton  = mouseLeftButton  && !(button == 0);
    mouseRightButton = mouseRightButton && !(button == 2);
}

bool Game::getMouseLeftButtonDown() const
{
    return !mouseLeftButtonLast && mouseLeftButton;
}

bool Game::getMouseRightButtonDown() const
{
    return !mouseRightButtonLast && mouseRightButton;
}

glm::ivec2 Game::getMousePosScreen() const
{
	return mousePos;
}

glm::ivec2 Game::getMousePosWorld() const
{
    glm::ivec2 mousePosScreen = getMousePosScreen();
	glm::vec4 v4 = glm::vec4(mousePosScreen.x, mousePosScreen.y, 0, 1);
    SceneGame *sceneGame = dynamic_cast<SceneGame*>(currentScene);
    if (sceneGame)
    {
        v4 = glm::inverse(sceneGame->getCamera()->getView()) * v4; // Pass to world space
    }
    return glm::ivec2(v4.x, v4.y);
}

bool Game::getMouseLeftButton() const
{
    return mouseLeftButton;
}

bool Game::getMouseRightButton() const
{
    return mouseRightButton;
}

bool Game::getKeyUp(int key) const
{
    return keysLast[key] && !keys[key];
}

bool Game::getKeyDown(int key) const
{
    return !keysLast[key] && keys[key];
}


bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

SoundManager* Game::getSoundManager() {
    return soundManager;
}





