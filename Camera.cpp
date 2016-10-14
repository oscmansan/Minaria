#include "Camera.h"

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "SceneGame.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	position = glm::vec2(0.0f);
}

Camera::~Camera()
{
}

void Camera::init(const glm::ivec2 &playerPosition)
{
	initialOffset = glm::ivec2(-SCREEN_WIDTH / 2 + 16/2, -SCREEN_HEIGHT / 2 + 32/2);
}

void Camera::update()
{
    Player *player = Game::getCurrentSceneGame()->getPlayer();
	glm::ivec2 playerPosWorld = player->getPosition();
	position = playerPosWorld + initialOffset;

	glm::ivec2 playerPosScreen = player->getScreenPosition();
}

glm::mat4 Camera::getView() const
{
	glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(position,0) );
	return glm::inverse(m);
}

void Camera::setPosition(const glm::ivec2 &position)
{
	this->position = position;
}

const glm::ivec2& Camera::getPosition()
{
	return position;
}
