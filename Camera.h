#pragma once

#include <glm/glm.hpp>

class Camera
{
private:
	glm::ivec2 position;
	glm::ivec2 initialOffset;

public:
	Camera();
	~Camera();

	void init(const glm::ivec2 &playerPosition);
	void update();
	glm::mat4 getView() const;
	
	void setPosition(const glm::ivec2 &position);
	const glm::ivec2& getPosition();
};

