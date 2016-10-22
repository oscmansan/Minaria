#ifndef ISCENENODE_H
#define ISCENENODE_H

#include <glm/glm.hpp>

#include "ShaderProgram.h"

class ISceneNode
{
public:
    virtual ~ISceneNode();

    virtual void init() {}
    virtual void update(int deltaTime) {}
    virtual void render(ShaderProgram &program) {}

    virtual void prepareModelViewMatrix() const;
    virtual void prepareModelViewMatrix(const glm::ivec2 &pos) const;
    virtual void setPosition(const glm::ivec2 &position);
    virtual const glm::ivec2& getPosition() const;
    virtual glm::ivec2 getSize() const { return glm::ivec2(0,0); }

    bool isScreenNode() const;

protected:
    bool isScreen = false;

    ISceneNode();

    glm::ivec2 position;
    float rotation = 0.0f;
};

#endif // SCENENODE_H
