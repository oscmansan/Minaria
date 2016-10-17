#include "Background.h"

Background::Background(ShaderProgram &program)
{
    this->program = &program;

    string file[5];
    file[0] = "images/layer_01.png";
    file[1] = "images/layer_02.png";
    file[2] = "images/layer_03.png";
    file[3] = "images/layer_04.png";
    file[4] = "images/layer_05.png";

    for (int i = 0; i < 5; ++i) {
        texture[i].loadFromFile(file[i], TEXTURE_PIXEL_FORMAT_RGBA);
        texture[i].setWrapS(GL_REPEAT);
        texture[i].setWrapT(GL_REPEAT);
        texture[i].setMinFilter(GL_NEAREST);
        texture[i].setMagFilter(GL_NEAREST);
    }

    float height = SCREEN_HEIGHT;
    float width = SCREEN_WIDTH;

    float vertices[24] = {0.f, 0.f, 0.f, 0.f,
                          width, 0.f, 1.f, 0.f,
                          width, height, 1.f, 1.f,
                          0.f, 0.f, 0.f, 0.f,
                          width, height, 1.f, 1.f,
                          0.f, height, 0.f, 1.f};

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
    posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
    texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

void Background::update(int deltaTime) {
    Player *player = Game::getCurrentSceneGame()->getPlayer();
    glm::vec2 v = player->getVelocity();

    // Parallax
    offset[0] += v.x/SCREEN_WIDTH/25;
    offset[1] += v.x/SCREEN_WIDTH/20;
    offset[2] += v.x/SCREEN_WIDTH/15;
    offset[3] += v.x/SCREEN_WIDTH/10;
    offset[4] += v.x/SCREEN_WIDTH/5;
}

void Background::render() {
    glEnable(GL_TEXTURE_2D);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(posLocation);
    glEnableVertexAttribArray(texCoordLocation);
    for (int i = 0; i < 5; ++i) {
        program->setUniform4f("tint", 1, 1, 1, 0);
        program->setUniform2f("texCoordDispl", offset[i], 0.4f);
        texture[i].use();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glDisable(GL_TEXTURE_2D);
}

void Background::free()
{
    for (int i = 0; i < 5; ++i) {
        glDeleteBuffers(1, &vbo);
    }
}
