#include "Text.h"

#include "Game.h"
#include "Scene.h"

Texture *Text::textSheet = NULL;
glm::vec2 Text::letterSizeInTextsheet = glm::vec2(1.0f / 32, 1.0f / 3.1f);

Text::Text()
{
    if (!Text::textSheet)
    {
        Text::textSheet = new Texture();
        Text::textSheet->loadFromFile("images/textsheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    }
}

void Text::render()
{
    if (letterSprites.size() <= 0 || !visible) return;
    glm::ivec2 letterSize = letterSprites.front()->getSize(); // The first char cant be a space !!!

    //Apply color
    for (Sprite *letterSprite : letterSprites)
    {
        if (letterSprite) letterSprite->setTint(color);
    }

    ShaderProgram *program = Scene::getShaderProgram();

    glm::ivec2 currentPos = position;
    for (Sprite *letterSprite : letterSprites)
    {
        if (letterSprite != NULL) // NULL = Space char
        {
            program->setUniformMatrix4f("view", glm::mat4(1.0f));
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(currentPos.x, currentPos.y, 0.f));
            program->setUniformMatrix4f("model", model);
            letterSprite->render();
        }

        currentPos.x += letterSize.x;
    }
}

void Text::setPosition(const glm::ivec2 &pos)
{
    position = pos;
}

void Text::setColor(const glm::vec4 &color)
{
    this->color = color;
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

            if (c != ' ')
            {
                letterSprite->addKeyframe(0, letterSizeInTextsheet * glm::vec2(framePosX, framePosY));
                letterSprite->changeAnimation(0);
            }
            else
            {
                delete letterSprite;
                letterSprite = NULL; // A NULL means a space
            }

            letterSprites.push_back(letterSprite); // A NULL means a space
        }
        currentText = str;
    }
}

void Text::centerHorizontally()
{
    position.x = (Game::getScreenWidth() - getBoundingRect().width) / 2;
}

void Text::setVisible(bool visible)
{
    this->visible = visible;
}

Rect Text::getBoundingRect() const
{
    if (letterSprites.size() <= 0) return Rect(0,0,0,0);

    glm::ivec2 letterSize = letterSprites.front()->getSize();
    return Rect(position.x, position.y, currentText.length() * letterSize.x, letterSize.y);
}
