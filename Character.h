#ifndef _CHARACTER_INCLUDE
#define _CHARACTER_INCLUDE

#include "Rect.h"
#include "Sprite.h"
#include "ISceneNode.h"

#include <glm/gtc/matrix_transform.hpp>

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

class TileMap;
class Character : public ISceneNode
{
public:
	Character();
    virtual ~Character();

protected:
	enum CharacterAnims
	{
		STAND_RIGHT, STAND_LEFT, MOVE_LEFT, MOVE_RIGHT
	};

    virtual void move(int deltaTime);
	virtual void processCollisions();
	virtual void jump();
	void applyGravity();

public:
    virtual void init() override;
    virtual void update(int deltaTime) override;
    virtual void render(ShaderProgram &program) override;
	
    void setTileMap(TileMap *tileMap);
    glm::ivec2 getSize();

	bool isGrounded();

    glm::ivec2 getScreenPosition() const;
	Rect getBoundingBox() const;
    glm::vec2 getVelocity() const;
	
protected:
	bool bJumping;

	glm::vec2 velocity = glm::vec2(0.0f);
	float gravity;
	float jumpSpeed;
	float maxFallSpeed;

	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};


#endif // _PLAYER_INCLUDE


