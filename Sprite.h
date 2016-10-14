#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE


#include <vector>
#include <glm/glm.hpp>

#include "ShaderProgram.h"
#include "AnimKeyframes.h"
#include "Texture.h"


// This class is derived from code seen earlier in TexturedQuad but it is also
// able to manage animations stored as a spritesheet. 


class Sprite
{

public:
	// Textured quads can only be created inside an OpenGL context
	static Sprite *createSprite(const glm::ivec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

	Sprite(const glm::ivec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

	void update(int deltaTime);
	void render() const;
	void free();

	void setNumberAnimations(int nAnimations);
	void setAnimationSpeed(int animId, int keyframesPerSec);
	void addKeyframe(int animId, const glm::vec2 &frame);
	void changeAnimation(int animId);
	int animation() const;

	glm::ivec2 getSize() const;

	void setVisible(bool visible);
	bool isVisible() const;

    void setTint(const glm::vec4 &tint);
	glm::vec4 getTint() const;

    void setTexture(Texture *texture);

private:
    Texture *texture = NULL;
    ShaderProgram *shaderProgram = NULL;
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 size;
	glm::vec4 tint = glm::vec4(1, 1, 1, 0);
	bool visible = true;
	int currentAnimation, currentKeyframe;
	float timeAnimation;
	glm::vec2 texCoordDispl;
	vector<AnimKeyframes> animations;

};


#endif // _SPRITE_INCLUDE

