#include "Background.h"

Background::Background(ShaderProgram &program)
{
    this->program = program;

    const string file = "images/background.png";
    texture.loadFromFile(file, TEXTURE_PIXEL_FORMAT_RGBA);
    texture.setWrapS(GL_REPEAT);
    texture.setWrapT(GL_REPEAT);
    texture.setMinFilter(GL_NEAREST);
    texture.setMagFilter(GL_NEAREST);

    float vertices[24] = {0.f, 0.f, 0.f, 0.f,
                          SCREEN_WIDTH, 0.f, 1.f, 0.f,
                          SCREEN_WIDTH, SCREEN_HEIGHT, 1.f, 1.f,
                          0.f, 0.f, 0.f, 0.f,
                          SCREEN_WIDTH, SCREEN_HEIGHT, 1.f, 1.f,
                          0.f, SCREEN_HEIGHT, 0.f, 1.f};

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
    posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
    texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

void Background::render() {
    texCoordDispl = glm::vec2(Scene::getCurrentTime()/10000.f,0.f);
    shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);
    glEnable(GL_TEXTURE_2D);
    texture.use();
    glBindVertexArray(vao);
    glEnableVertexAttribArray(posLocation);
    glEnableVertexAttribArray(texCoordLocation);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisable(GL_TEXTURE_2D);
}

void Background::update(int deltaTime) {

}

void Background::free()
{
    glDeleteBuffers(1, &vbo);
}
