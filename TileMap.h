#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "Block.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(glm::ivec2 size, ShaderProgram &program);
	static TileMap *createTileMap(const string &levelFile, ShaderProgram &program);

	TileMap(glm::ivec2 size, ShaderProgram &program);
	TileMap(const string &levelFile, ShaderProgram &program);
	~TileMap();

	void render();
	void free();
	
	int getTileSize() const { return tileSize; }
	glm::ivec2 getTotalSizeWorld() const;
	glm::ivec2 getTotalSizeTiles() const;

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;

    bool addTile(const glm::ivec2 &posWorld, int type, bool mustUpdateVAO = true);
    void delTile(const glm::ivec2 &posWorld, bool mustUpdateVAO = true);
    int getTileAt(const glm::ivec2 &posWorld) const;
    Block::Type getBlock(const glm::ivec2 &posWorld) const;

    void updateVAO();
    void createBg();

private:
    glm::ivec2 worldPosToTilePos(const glm::ivec2 &posWorld) const;
    int tilePosToIndex(const glm::ivec2 &posTile) const;
    int worldPosToIndex(const glm::ivec2 &posWorld) const;

    bool loadLevel(const string &levelFile);

private:
    GLuint vao;
    GLuint vbo;
	GLint posLocation, texCoordLocation;
	ShaderProgram *program;
	glm::ivec2 mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
    int *map;
};


#endif // _TILE_MAP_INCLUDE


