#include <GL/glew.h>
#include <GL/glut.h>

#include "Game.h"
#include "Camera.h"

void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
    for (int i = 0; i < 256; ++i) { keysLast[i] = keys[i]; }
    for (int i = 0; i < 256; ++i) { specialKeysLast[i] = specialKeys[i]; }
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
	mouseLeftButtonDown  = (button == 0);
	mouseRightButtonDown = (button == 2);
}

void Game::mouseRelease(int button)
{
	mouseLeftButtonDown  = mouseLeftButtonDown  && !(button == 0);
	mouseRightButtonDown = mouseRightButtonDown && !(button == 2);
}

bool Game::getMouseLeftButtonDown() const
{
	return mouseLeftButtonDown;
}

bool Game::getMouseRightButtonDown() const
{
	return mouseRightButtonDown;
}

glm::ivec2 Game::getMousePosScreen() const
{
	return mousePos;
}

glm::ivec2 Game::getMousePosWorld() const
{
    glm::ivec2 mousePosScreen = getMousePosScreen();
	glm::vec4 v4 = glm::vec4(mousePosScreen.x, mousePosScreen.y, 0, 1);
	v4 = glm::inverse(Scene::getCamera()->getView()) * v4; // Pass to world space
	return glm::ivec2(v4.x, v4.y);
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





