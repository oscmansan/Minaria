#include "Camera.h"

#include "Game.h"
#include "Scene.h"
#include "Player.h"

#include <glm/gtc/matrix_transform.hpp>

#include "SceneGame.h"
#include "Game.h"

Camera::Camera()
{
	position = glm::vec2(0.0f);
}

Camera::~Camera()
{
}

void Camera::init(const glm::ivec2 &playerPosition)
{
    initialOffset = glm::ivec2(-Game::getScreenWidth() / 2 + 16/2, -Game::getScreenHeight() / 2 + 32/2);
}

void Camera::update(int deltaTime)
{
    Player *player = Game::getCurrentSceneGame()->getPlayer();
	glm::ivec2 playerPosWorld = player->getPosition();
    setPosition(playerPosWorld + initialOffset);

    if (trembleChrono < trembleTime)
    {
        setPosition(getPosition() + glm::ivec2(rand() % 3 - 1, rand() % 3 - 1) * trembleAmount);
        trembleChrono += deltaTime;
    }

    totalRotation += spinSpeed;

    if (zoomTimeChrono < zoomTimeTarget)
    {
        zoomTimeChrono += deltaTime;
        zoom = 1.0f + (zoomTarget - 1) * (float(zoomTimeChrono) / zoomTimeTarget);
    }
}

const glm::mat4 &Camera::getView() const
{
    return view;
}

void Camera::setPosition(const glm::ivec2 &position)
{
	this->position = position;
    glm::mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, glm::vec3(position,0) );
    glm::ivec2 screenSize = glm::ivec2(Game::instance().getScreenWidth(), Game::instance().getScreenHeight());
    m = glm::translate(m, glm::vec3(screenSize / 2, 0) );
    m = glm::rotate(m, totalRotation, glm::vec3(0, 0, 1.0f));
    m = glm::scale(m, glm::vec3(1.0f/zoom));
    m = glm::translate(m, glm::vec3(-screenSize / 2, 0) );
    view = glm::inverse(m);
}

const glm::ivec2& Camera::getPosition()
{
    return position;
}

void Camera::tremble(int amount, int time)
{
    trembling = true;
    trembleChrono = 0;
    trembleTime = max(trembleTime, time);
    trembleAmount = amount;
}

void Camera::spin(float speed, int time)
{
    spinSpeed = speed;
}

void Camera::zoomIn(float zoom, int time)
{
    zoomTarget = zoom;
    zoomTimeTarget = time;
    zoomTimeChrono = 0;
}
