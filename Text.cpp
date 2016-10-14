#include "Text.h"

#include "Scene.h"

Texture *Text::textSheet = NULL;
glm::vec2 Text::letterSizeInTextsheet = glm::vec2(1.0f / 32, 1.0f / 3);

Text::Text()
{
    if (!Text::textSheet)
    {
        Text::textSheet = new Texture();
        Text::textSheet->loadFromFile("images/textsheet2.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
}

void Text::render()
{
    ShaderProgram *program = Scene::getShaderProgram();
    glm::ivec2 currentPos = position;
    for (Sprite *letterSprite : letterSprites)
    {
        program->setUniformMatrix4f("view", glm::mat4(1.0f));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(currentPos.x, currentPos.y, 0.f));
        program->setUniformMatrix4f("model", model);
        letterSprite->render();
        currentPos.x += letterSprite->getSize().x;
    }
}

void Text::setPosition(const glm::ivec2 &pos)
{
    position = pos;
}

void Text::setColor(const glm::vec4 &color)
{
    for (Sprite *letterSprite : letterSprites)
    {
        letterSprite->setTint(color);
    }
}

void Text::setText(const std::string &str, int size)
{
    ShaderProgram *program = Scene::getShaderProgram();
    if (currentText != str) // Avoid useless updates
    {
        for (Sprite *letterSprite : letterSprites)
        {
            if (letterSprite) delete letterSprite;
        }
        letterSprites.clear();

        for (int i = 0; i < str.length(); ++i)
        {
            char c = str[i];
            Sprite *letterSprite = Sprite::createSprite(glm::ivec2(size),
                                                        letterSizeInTextsheet,
                                                        Text::textSheet,
                                                        program);
            letterSprite->setNumberAnimations(1);

            int framePosX = 0;
            int framePosY = 0;
            if (c >= 'a' && c <= 'z')
            {
                framePosX = int(c - 'a');
                framePosY = 2;
            }
            else if (c >= 'A' && c <= 'Z')
            {
                framePosX = int(c - 'A');
                framePosY = 1;
            }
            else if (c >= '0' && c <= '9')
            {
                framePosX = int(c - '0') + 15;
                framePosY = 0;
            }
            else if (c == '.') { framePosX = 13; framePosY = 0; }

            letterSprite->addKeyframe(0, letterSizeInTextsheet * glm::vec2(framePosX, framePosY));
            letterSprite->changeAnimation(0);

            letterSprites.push_back(letterSprite);
        }
        currentText = str;
    }
}
