#include "ISceneNode.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"

ISceneNode::ISceneNode()
{
}

ISceneNode::~ISceneNode()
{
}

void ISceneNode::prepareModelViewMatrix(ShaderProgram *program) const
{
    prepareModelViewMatrix(position, glm::vec2(1.0f), program);
}

void ISceneNode::prepareModelViewMatrix(const glm::ivec2 &pos, const glm::vec2 &scale, ShaderProgram *program) const
{
    Scene *scene = Game::getCurrentScene(); if (!scene) return;
    program = program ? program : scene->getShaderProgram(); if (!program) return;
    program->use();

    program->setUniformMatrix4f("projection", scene->getProjection());
    SceneGame *sceneGame = Game::getCurrentSceneGame();
    if (sceneGame)
    {
        Player *player = sceneGame->getPlayer();
        if ( !player->winSymbol || (this != player->winSymbol && this != player->winSymbol->replayText) )
        {
            if (player->winSymbol)
            {
                program->setUniform1f("grayAmount", player->winSymbol->getGrayAmount());
            }
            else
            {
                program->setUniform1f("grayAmount", player->timeSinceDead / player->timeToDie);
            }
        }
        else program->setUniform1f("grayAmount", 0.0f);
    }

    program->setUniform2f("windowSize", Game::getScreenWidth(), Game::getScreenHeight());

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

void ISceneNode::setIsScreen(bool screen)
{
    isScreen = screen;
}

bool ISceneNode::isScreenNode() const
{
    return isScreen;
}
