#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Game.h"

class Background
{
public:
    Background(ShaderProgram &program);
    ~Background();

    void update(int deltaTime);
    void render();
    void free();

private:
    GLuint vao;
    GLuint vbo;
    GLint posLocation, texCoordLocation;
    ShaderProgram *program;
    Texture texture[5];
    float offset[5];
};

#endif // BACKGROUND_H