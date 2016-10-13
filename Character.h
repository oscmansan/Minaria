#ifndef _CHARACTER_INCLUDE
#define _CHARACTER_INCLUDE

#include "Rect.h"
#include "Sprite.h"

#include <glm/gtc/matrix_transform.hpp>

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

class TileMap;
class Character
{
public:
	Character();
	virtual ~Character();

protected:
	enum CharacterAnims
	{
		STAND_RIGHT, STAND_LEFT, MOVE_LEFT, MOVE_RIGHT
	};

	virtual void move(int deltaTime) = 0;
	virtual void processCollisions();
	virtual void jump();
	void applyGravity();

public:
	virtual void init(ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
	virtual void render(ShaderProgram &program);
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::ivec2 &pos);

	bool isGrounded();

	glm::ivec2 getScreenPosition() const;
	glm::ivec2 getPosition() const;
	Rect getBoundingBox() const;
	
protected:
	bool bJumping;

	glm::vec2 velocity = glm::vec2(0.0f);
	float gravity;
	float jumpSpeed;
	float maxFallSpeed;

	glm::ivec2 position;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};


#endif // _PLAYER_INCLUDE


