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


// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class TileMap;
class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	static Scene *getInstance();
	static int getCurrentTime();
	static Player *getPlayer();
	static Camera *getCamera();
	static TileMap *getTileMap();
    static ShaderProgram *getShaderProgram();

	Character* whosThere(const glm::ivec2 &pos);

private:
	static Scene* singleton;

	void initShaders();

private:
	Player *player;
	Camera *camera;
    Texture textureBg;
    Sprite *spriteBg = NULL;
	std::list<Character*> characters;

    TileMap *map, *mapBg;
	ShaderProgram texProgram;
	int currentTime;
	glm::mat4 projection;

    void generateProceduralTilemap();
};


#endif // _SCENE_INCLUDE

