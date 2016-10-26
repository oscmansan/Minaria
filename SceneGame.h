#ifndef _SCENEGAME_INCLUDE
#define _SCENEGAME_INCLUDE

#include <list>
#include <glm/glm.hpp>

#include "Scene.h"
#include "GroundEnemy.h"
#include "FlyingEnemy.h"
#include "Camera.h"
#include "Player.h"
#include "Character.h"
#include "PerlinNoise.h"
#include "ShaderProgram.h"

#include "Text.h"
#include "SoundManager.h"

// SceneGame contains all the entities of our game.
// It is responsible for updating and render them.

class TileMap;
class Background;

class SceneGame : public Scene
{

public:
    SceneGame();
    virtual ~SceneGame();

    void init() override;
    void update(int deltaTime) override;
    void renderBackLayer() override;
    void render() override;
    void renderOverlay() override;
    Player *getPlayer() const;
    Camera *getCamera() const;
    TileMap *getTileMap() const;
    const std::list<Character*>& getCharacters() const;

    std::list<Character*> whosThere(const glm::ivec2 &pos);
    std::list<Character*> whosThereTile(const glm::ivec2 &posTileWorld);

    void removeCharacter(Character *character);

    SoundManager* getSoundManager();

private:
    Player *player = NULL;
    Camera *camera = NULL;
    std::list<Character*> characters;
    std::list<Text*> texts;

    Background *background = NULL;

    TileMap *map = NULL;
    TileMap *mapBg = NULL;

    SoundManager* soundManager = NULL;

    void generateProceduralTilemap();
};


#endif // _SCENEGAME_INCLUDE

