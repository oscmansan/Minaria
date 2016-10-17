#ifndef _SCENEGAME_INCLUDE
#define _SCENEGAME_INCLUDE

#include <list>
#include <glm/glm.hpp>

#include "Scene.h"
#include "Enemy.h"
#include "Camera.h"
#include "Player.h"
#include "Character.h"
#include "PerlinNoise.h"
#include "ShaderProgram.h"

#include "Text.h"

// SceneGame contains all the entities of our game.
// It is responsible for updating and render them.

class TileMap;
class Background;

class SceneGame : public Scene
{

public:
    SceneGame();
    ~SceneGame();

    void init() override;
    void update(int deltaTime) override;
    void render() override;

    Player *getPlayer() const;
    Camera *getCamera() const;
    TileMap *getTileMap() const;

    Character* whosThere(const glm::ivec2 &pos);

private:
    Player *player = NULL;
    Camera *camera = NULL;
    std::list<Character*> characters;
    std::list<Text*> texts;

    Background *background = NULL;

    TileMap *map = NULL;
    TileMap *mapBg = NULL;

    void generateProceduralTilemap();
};


#endif // _SCENEGAME_INCLUDE
