#include "Text.h"

#include "Game.h"
#include "Scene.h"

ShaderProgram Text::program;
Texture *Text::textSheet1 = NULL;
Texture *Text::textSheet2 = NULL;
Texture *Text::textSheet3 = NULL;
glm::vec2 Text::letterSizeInTextsheet = glm::vec2(1.0f / 32, 1.0f);

Text::Text()
{
    isScreen = true;

    if (!Text::textSheet1)
    {
        Text::textSheet1 = new Texture();
        Text::textSheet1->loadFromFile("images/textsheet1.png", TEXTURE_PIXEL_FORMAT_RGBA);
        Text::textSheet2 = new Texture();
        Text::textSheet2->loadFromFile("images/textsheet2.png", TEXTURE_PIXEL_FORMAT_RGBA);
        Text::textSheet3 = new Texture();
        Text::textSheet3->loadFromFile("images/textsheet3.png", TEXTURE_PIXEL_FORMAT_RGBA);
        Text::textSheet1->setMinFilter(GL_NEAREST);
        Text::textSheet1->setMagFilter(GL_NEAREST);
        Text::textSheet2->setMagFilter(GL_NEAREST);
        Text::textSheet2->setMinFilter(GL_NEAREST);
        Text::textSheet3->setMinFilter(GL_NEAREST);
        Text::textSheet3->setMagFilter(GL_NEAREST);
        Text::textSheet1->setWrapS(GL_CLAMP);
        Text::textSheet1->setWrapT(GL_CLAMP);
        Text::textSheet2->setWrapS(GL_CLAMP);
        Text::textSheet2->setWrapT(GL_CLAMP);
        Text::textSheet3->setWrapS(GL_CLAMP);
        Text::textSheet3->setWrapT(GL_CLAMP);
    }

    if (!Text::program.isLinked())
    {
        Shader vShader, fShader;
        vShader.initFromFile(VERTEX_SHADER, "shaders/text.vert");
        if (!vShader.isCompiled())
        {
            cout << "Vertex Shader Error" << endl << "" << vShader.log() << endl << endl;
        }

        fShader.initFromFile(FRAGMENT_SHADER, "shaders/text.frag");
        if (!fShader.isCompiled())
        {
            cout << "Fragment Shader Error" << endl << "" << fShader.log() << endl << endl;
        }

        Text::program.init();
        Text::program.addShader(vShader);
        Text::program.addShader(fShader);
        Text::program.link();

        if(!Text::program.isLinked())
        {
            cout << "Shader Linking Error" << endl << "" << Text::program.log() << endl << endl;
        }
        Text::program.bindFragmentOutput("outColor");
        vShader.free(); fShader.free();
    }

    setStroke(3, glm::vec4(0,0,0,1));
}

Text::~Text()
{
}

void Text::render(ShaderProgram &program)
{
    if (letterSprites.size() <= 0 || !visible) return;
    glm::ivec2 letterSize = letterSprites.front()->getSize(); // The first char cant be a space !!!

    //Apply color
    for (Sprite *letterSprite : letterSprites)
    {
        if (letterSprite) letterSprite->setTint(color);
    }

    glm::ivec2 currentPos = position;
    for (Sprite *letterSprite : letterSprites)
    {
        if (letterSprite != NULL) // NULL = Space char
        {
            prepareModelViewMatrix(currentPos, glm::vec2(1.0f), letterSprite->getShaderProgram());
            letterSprite->getShaderProgram()->setUniform1f("stroke", stroke);
            letterSprite->getShaderProgram()->setUniform4f("strokeColor", strokeColor.x, strokeColor.y,
                                                           strokeColor.z, strokeColor.w);
            letterSprite->getShaderProgram()->setUniform2f("textureSize", 1024, 36);
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
    if (currentText != str || this->size != size) // Avoid useless updates
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
                                                        Text::textSheet1,
                                                        &Text::program);
            letterSprite->setNumberAnimations(1);
            letterSprite->setShaderProgram(Text::program);

            int framePosX = 0;
            int framePosY = 0;
            if (c >= 'a' && c <= 'z')
            {
                framePosX = int(c - 'a');
                framePosY = 0;
                letterSprite->setTexture(Text::textSheet3);
            }
            else if (c >= 'A' && c <= 'Z')
            {
                framePosX = int(c - 'A');
                framePosY = 0;
                letterSprite->setTexture(Text::textSheet2);
            }
            else if (c >= '0' && c <= '9')
            {
                framePosX = int(c - '0') + 15;
                framePosY = 0;
                letterSprite->setTexture(Text::textSheet1);
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
    this->size = size;
}

void Text::centerHorizontally()
{
    position.x = (Game::getScreenWidth() - getBoundingRect().width) / 2;
}

void Text::setVisible(bool visible)
{
    this->visible = visible;
}

void Text::setStroke(int stroke, const glm::vec4 &strokeColor)
{
    this->stroke = stroke;
    this->strokeColor = strokeColor;
}

Rect Text::getBoundingRect() const
{
    if (letterSprites.size() <= 0) return Rect(0,0,0,0);

    glm::ivec2 letterSize = letterSprites.front()->getSize();
    return Rect(position.x, position.y, currentText.length() * letterSize.x, letterSize.y);
}
