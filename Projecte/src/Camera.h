#pragma once

#include <glm/glm.hpp>

class Camera
{
private:
	glm::ivec2 position;
	glm::ivec2 initialOffset;
    glm::mat4 view;

    bool trembling = false;
    int trembleTime = 0;
    int trembleChrono = trembleTime;
    int trembleAmount = 0;

    float zoom = 1.0f;
    float zoomTarget = 1.0f;
    int zoomTimeTarget = 0;
    int zoomTimeChrono = 0;

    float totalRotation = 0.0;
    float spinSpeed = 0.0;

public:
	Camera();
	~Camera();

	void init(const glm::ivec2 &playerPosition);
    void update(int deltaTime);
    const glm::mat4 &getView() const;
	
	void setPosition(const glm::ivec2 &position);
	const glm::ivec2& getPosition();

    void tremble(int amount = 1, int time = 500);
    void spin(float speed = 1.0f, int time = 500);
    void zoomIn(float zoom = 1.0f, int time = 500);
};

