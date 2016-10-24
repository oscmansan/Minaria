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
    tileSize = 24;

    mapSize = size;
    map = std::vector<Tile*>(mapSize.x * mapSize.y, NULL);
}

TileMap::~TileMap()
{
    for (int i = 0; i < map.size(); ++i)
    {
        if (map[i] != NULL)
        {
            delete map[i];
        }
    }
    free();
}


void TileMap::render()
{
    TileMap *foreground = Game::getCurrentSceneGame()->getTileMap();
    for (Tile *tile : map)
    {
        if (tile)
        {
            bool drawTile = true;
            if (isBg)
            {
                // Only draw the tiles that the foreground dont cover up
                drawTile = (foreground->getTileAt(tile->getPosition()) == NULL);
            }

            if (drawTile)
            {
                if ( tile->isVisible() )
                {
                    if (isBg)
                    {
                        float bgTint = 0.4f;
                        tile->getSprite()->setTint( glm::vec4(bgTint) );
                    }
                    else
                    {
                        tile->getSprite()->setTint( glm::vec4(1.0f) );
                    }
                    tile->render();
                }
            }
        }
    }
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
            if (pos.y <= tileSize * y + tileSize)
			{
                *posY = tileSize * y + tileSize;
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

int TileMap::getSurfaceLevel(int x) {
    for (int y = 0; y < mapSize.y*tileSize; y += tileSize) {
        Block *b = getBlock(glm::ivec2(x,y));
        if (b)
            return y;
    }
    return 0;
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





















