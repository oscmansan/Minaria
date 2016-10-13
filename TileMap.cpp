#include "TileMap.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define GLM_SWIZZLE
#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"
#include "Tile.h"
#include "Block.h"

using namespace std;


TileMap *TileMap::createTileMap(glm::ivec2 size, ShaderProgram &program)
{
	TileMap *map = new TileMap(size, program);
	return map;
}

TileMap::TileMap(glm::ivec2 size, ShaderProgram &program)
{
	this->program = &program;

	// Specify sizes
	mapSize = size;
    tileSize = 16;                   //
    blockSize = 32;                  //

	// Tilesheet related
	const string tilesheetFile = "images/blocks.png";  // Tilesheet location
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	tilesheetSize = glm::ivec2(2, 2); // Number of tiles in the tilesheet
	tileTexSize   = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	//

    map = std::vector<Tile*>(mapSize.x * mapSize.y, NULL);
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
            map[j * mapSize.x + i] = NULL;
		}
    }
}

TileMap::~TileMap()
{
}


void TileMap::render()
{
	glEnable(GL_TEXTURE_2D);

    glm::mat4 view = Scene::getCamera()->getView();
    for (Tile *tile : map)
    {
        if (tile)
        {
            // +-50 to render a bit more than needed;
            Rect screenRect = Rect(-50, -50, SCREEN_WIDTH+50, SCREEN_HEIGHT+50);
            glm::vec4 v4 = (view * glm::vec4(tile->getPosition(),0,1));
            bool isVisible = screenRect.contains( glm::ivec2(v4.x, v4.y) );
            if (isVisible)
            {
                tile->render();
            }
        }
    }

    glDisable(GL_TEXTURE_2D);
}

void TileMap::update(int deltaTime)
{
    for(Tile *t : map)
    {
        if (t)
        {
            t->update(deltaTime);
        }
    }
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

glm::ivec2 TileMap::getTotalSizeTiles() const
{
	return mapSize;
}

glm::ivec2 TileMap::getTotalSizeWorld() const
{
	return getTotalSizeTiles() * getTileSize();
}


// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;

	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x+x] != 0)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;

	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x+x] != 0)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y*mapSize.x + x] != 0)
		{
			if (pos.y - tileSize * y - size.y <= 4)
			{
				*posY = tileSize * (y-1) + size.y;
				return true;
			}
		}
	}

	return false;
}


bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for(int x=x0; x<=x1; x++)
	{
		if(map[y*mapSize.x+x] != 0)
		{
			if (pos.y - tileSize * y + size.y <= 4)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}
	
	return false;
}

void TileMap::delTile(const glm::ivec2 &posWorld)
{
	int idx = worldPosToIndex(posWorld);
	if (idx >= 0 && idx < (mapSize.x * mapSize.y))
	{
        if (map[idx] != NULL)
        {
            delete map[idx];
            map[idx] = NULL;
        }
	}
}

Tile* TileMap::getTileAt(const glm::ivec2 &posWorld) const
{
	int idx = worldPosToIndex(posWorld);
    return ( idx >= 0 && idx < (mapSize.x * mapSize.y)) ? map[idx] : NULL;
}

Block* TileMap::getBlock(const glm::ivec2 &posWorld) const
{
    Tile *t = getTileAt(posWorld);
    return t ? dynamic_cast<Block*>(t) : NULL;
}

glm::ivec2 TileMap::worldPosToTilePos(const glm::ivec2 &posWorld) const
{
	return posWorld / tileSize;
}

int TileMap::tilePosToIndex(const glm::ivec2 &posTile) const
{
	return (posTile.y * mapSize.x) + posTile.x;
}

int TileMap::worldPosToIndex(const glm::ivec2 &posWorld) const
{
	return tilePosToIndex( worldPosToTilePos(posWorld) );
}





















