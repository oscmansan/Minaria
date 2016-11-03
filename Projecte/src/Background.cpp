#include "Background.h"

Background::Background(ShaderProgram &program)
{
    this->program = &program;

    string file[6];
    file[0] = "images/layer_01.png";
    file[1] = "images/parallax1.png";
    file[2] = "images/parallax3.png";
    file[3] = "images/parallax4.png";
    file[4] = "images/parallax5.png";
    file[5] = "images/parallax8.png";

    for (int i = 0; i < 6; ++i)
    {
        texture[i].loadFromFile(file[i], TEXTURE_PIXEL_FORMAT_RGBA);
        texture[i].setWrapS(GL_REPEAT);
        texture[i].setWrapT(GL_REPEAT);
        texture[i].setMinFilter(GL_NEAREST);
        texture[i].setMagFilter(GL_NEAREST);
    }

    float height = Game::getScreenHeight();
    float width = Game::getScreenWidth();

    float vertices[24] = {0.f, 0.f, 0.f, 0.f,
                          width, 0.f, 0.5f, 0.f,
                          width, height, 0.5f, 1.f,
                          0.f, 0.f, 0.f, 0.f,
                          width, height, 0.5f, 1.f,
                          0.f, height, 0.f, 1.f};

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
    posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
    texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

Background::~Background()
{
    free();
}

void Background::update(int deltaTime)
{
    Player *player = Game::getCurrentSceneGame()->getPlayer();
    glm::vec2 v = player->getVelocity();

    // Parallax
    offset[0] += v.x/Game::getScreenWidth()/30;
    offset[1] += v.x/Game::getScreenWidth()/25;
    offset[2] += v.x/Game::getScreenWidth()/20;
    offset[3] += v.x/Game::getScreenWidth()/15;
    offset[4] += v.x/Game::getScreenWidth()/10;
    offset[5] += v.x/Game::getScreenWidth()/5;
}

void Background::render()
{
    Player *player = Game::getCurrentSceneGame()->getPlayer();
    glBindVertexArray(vao);
    glEnableVertexAttribArray(posLocation);
    glEnableVertexAttribArray(texCoordLocation);
    for (int i = 0; i < 6; ++i)
    {
        program->setUniform4f("tint", 1, 1, 1, 0);
        program->setUniform2f("texCoordDispl", offset[i], 0.f);

        if (player->winSymbol)
        {
            program->setUniform1f("grayAmount", player->winSymbol->getGrayAmount());
        }
        else
        {
            program->setUniform1f("grayAmount", player->timeSinceDead / player->timeToDie);
        }

        program->setUniform2f("texCoordDispl", offset[i], 0.f);
        texture[i].use();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void Background::free()
{
    glDeleteBuffers(1, &vbo);
}
