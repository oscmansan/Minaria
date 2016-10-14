#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include <vector>

#include "Game.h"
#include "Tile.h"
#include "Block.h"
#include "Texture.h"
#include "SceneGame.h"
#include "ShaderProgram.h"

// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.
class TileMap
{

public:

    bool isBg = false;

	// Tile maps can only be created inside an OpenGL context
    static TileMap *createTileMap(glm::ivec2 size, ShaderProgram &program);

	TileMap(glm::ivec2 size, ShaderProgram &program);
	TileMap(const string &levelFile, ShaderProgram &program);
	~TileMap();

	void render();
    void update(int deltaTime);
	void free();
	
	int getTileSize() const { return tileSize; }
	glm::ivec2 getTotalSizeWorld() const;
	glm::ivec2 getTotalSizeTiles() const;

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;

    template<class T>
    T* addTile(const glm::ivec2 &posWorld)
    {
        if (Game::getCurrentSceneGame()->whosThere(posWorld)) return NULL;

        T* added = NULL;
        glm::ivec2 posTile = worldPosToTilePos(posWorld);
        int idx = worldPosToIndex(posWorld);
        if (idx >= 0 && idx < (mapSize.x * mapSize.y))
        {
            added = new T( glm::ivec2(posTile.x, posTile.y) * tileSize );
            map[idx] = added;
        }
        return added;
    }

    void delTile(const glm::ivec2 &posWorld);
    Tile* getTileAt(const glm::ivec2 &posWorld) const;
    Block* getBlock(const glm::ivec2 &posWorld) const;

private:
    glm::ivec2 worldPosToTilePos(const glm::ivec2 &posWorld) const;
    int tilePosToIndex(const glm::ivec2 &posTile) const;
    int worldPosToIndex(const glm::ivec2 &posWorld) const;

private:
    GLuint vao;
    GLuint vbo;
	GLint posLocation, texCoordLocation;
	ShaderProgram *program;
	glm::ivec2 mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;

    std::vector<Tile*> map;
};


#endif // _TILE_MAP_INCLUDE


