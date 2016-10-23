#include "ISceneNode.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"

ISceneNode::ISceneNode()
{
}

ISceneNode::~ISceneNode()
{
}

void ISceneNode::prepareModelViewMatrix() const
{
    prepareModelViewMatrix(position);
}

void ISceneNode::prepareModelViewMatrix(const glm::ivec2 &pos, const glm::vec2 &scale) const
{
    Scene *scene = Game::getCurrentScene(); if (!scene) return;
    ShaderProgram *program = scene->getShaderProgram(); if (!program) return;

    if (!isScreen && Game::getCurrentSceneGame()) program->setUniformMatrix4f("view", Game::getCurrentSceneGame()->getCamera()->getView());
    else program->setUniformMatrix4f("view", glm::mat4(1.0f));

    glm::mat4 model;
    model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.f));
    if (rotation != 0)
    {
        model = glm::translate(model, glm::vec3(getSize().x, getSize().y, 0.f) / 2.0f);
        model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around center
        model = glm::translate(model, -glm::vec3(getSize().x, getSize().y, 0.f) / 2.0f);
    }
    model = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0f));

    program->setUniformMatrix4f("model", model);
}

void ISceneNode::setPosition(const glm::ivec2 &position)
{
    this->position = position;
}

const glm::ivec2 &ISceneNode::getPosition() const
{
    return position;
}

bool ISceneNode::isScreenNode() const
{
    return isScreen;
}
