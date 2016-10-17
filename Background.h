#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Game.h"

class Background
{
public:
    Background(ShaderProgram &program);
    ~Background();

    void render();
    void update(int deltaTime);
    void free();

private:
    GLuint vao;
    GLuint vbo;
    GLint posLocation, texCoordLocation;
    ShaderProgram *program;
    Texture texture;
    glm::vec2 texCoordDispl;
};

#endif // BACKGROUND_H
