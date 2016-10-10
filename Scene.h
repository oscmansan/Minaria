#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <list>
#include <glm/glm.hpp>

#include "ShaderProgram.h"
#include "TileMap.h"
#include "Camera.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "PerlinNoise.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


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

	TileMap *map;
	ShaderProgram texProgram;
	int currentTime;
	glm::mat4 projection;

    void generateProceduralTilemap();
};


#endif // _SCENE_INCLUDE

