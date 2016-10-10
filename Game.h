#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include <iostream>
#include <glm/glm.hpp>

#include "Scene.h"

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

    glm::ivec2 getMousePosScreen() const;
	glm::ivec2 getMousePosWorld() const;
    bool getMouseLeftButton() const;
    bool getMouseRightButton() const;
	bool getMouseLeftButtonDown() const;
	bool getMouseRightButtonDown() const;
	bool getKey(int key) const;
    bool getKeyUp(int key) const;
    bool getKeyDown(int key) const;
	bool getSpecialKey(int key) const;

private:
	glm::ivec2 mousePos;
    bool mouseLeftButtonLast, mouseLeftButton;
    bool mouseRightButtonLast, mouseRightButton;

	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
                                      // we can have access at any time
    bool keysLast[256], specialKeysLast[256]; // Store last frame key states so that

};


#endif // _GAME_INCLUDE


