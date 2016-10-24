#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include <iostream>
#include <glm/glm.hpp>

#include "Scene.h"
#include "SceneMenu.h"
#include "SceneGame.h"
#include "SceneCredits.h"
#include "SoundManager.h"

using namespace std;

// Game is a singleton (a class with a single instance) that represents our whole application
class SceneGame;
class Game
{
public:
	Game() {}

    static Scene *getCurrentScene();
    static SceneGame *getCurrentSceneGame();
	
	static Game &instance()
	{
        static Game G;
		return G;
	}

    int InitialWidth  = 640;
    int InitialHeight = 480;
    static int getScreenWidth();
    static int getScreenHeight();
	
	void init();
	bool update(int deltaTime);
	void render();

    void gotoSceneMenu();
    void gotoSceneGame();
    void gotoSceneCredits();

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
    SoundManager* getSoundManager();

private:
    Scene *currentScene = NULL;
    Scene *nextScene = NULL;
    SoundManager* soundManager = NULL;

    glm::ivec2 mousePos;

    bool mouseLeftButtonLast, mouseLeftButton;
    bool mouseRightButtonLast, mouseRightButton;

    bool bPlay;                       // Continue to play game?
	bool keys[256], specialKeys[256]; // Store key states so that 
                                      // we can have access at any time
    bool keysLast[256], specialKeysLast[256]; // Store last frame key states so that

};


#endif // _GAME_INCLUDE


