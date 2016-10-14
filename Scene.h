#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <list>
#include <glm/glm.hpp>

#include "Enemy.h"
#include "Camera.h"
#include "Player.h"
#include "Character.h"
#include "PerlinNoise.h"
#include "ShaderProgram.h"

#include "Text.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class TileMap;
class Scene
{

public:
	Scene();
    virtual ~Scene();

    virtual void init();
    virtual void update(int deltaTime);
    virtual void _render();
    virtual void render() {}

    Text* createText(const std::string &str = "",
                  const glm::ivec2 &pos = glm::ivec2(0),
                  int size = 16);
    void deleteText(Text* text);

    static int getCurrentTime();
    static ShaderProgram *getShaderProgram();

protected:
	void initShaders();

    std::list<Text*> texts;

    ShaderProgram texProgram;
	int currentTime;
    glm::mat4 projection;
};


#endif // _SCENE_INCLUDE

