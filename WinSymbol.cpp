#include "WinSymbol.h"

#include "Game.h"
#include "SceneGame.h"

WinSymbol::WinSymbol() : ISceneNode()
{
    winTexture = new Texture();
    winTexture->loadFromFile("images/goldenNugget.png", TEXTURE_PIXEL_FORMAT_RGBA);

    replayText = Game::getCurrentSceneGame()->createText("Replay", glm::ivec2(0, 400), 30);
    replayText->centerHorizontally();
    replayText->setVisible(false);

    ShaderProgram *program = Game::getCurrentSceneGame()->getShaderProgram();
    winSprite = Sprite::createSprite(glm::ivec2(32), glm::vec2(1.0f), winTexture, program);

    Game::getCurrentScene()->addSceneNode(this);
}

WinSymbol::~WinSymbol()
{
    delete winSprite;
    delete winTexture;
}

void WinSymbol::init()
{
    ISceneNode::init();
}

void WinSymbol::update(int deltaTime)
{
    ISceneNode::update(deltaTime);

    timeSinceBegin += deltaTime;

    if (scale < maxScale && timeSinceBegin >= 500)
    {
        scale += 0.05f;
        scale = min(scale, maxScale);
        if (scale >= maxScale) timeSinceBegin = 0;
    }

    if (scale >= maxScale)
    {
        timeSinceBegin += deltaTime;
        if (timeSinceBegin >= 1000)
        {
            replayText->setVisible(true);
            glm::ivec2 mousePos = Game::instance().getMousePosScreen();
            if (replayText->getBoundingRect().contains(mousePos))
            {
                replayText->setColor(glm::vec4(0.5, 1, 0, 1));
                if (Game::instance().getMouseLeftButtonDown())
                {
                    Game::getCurrentSceneGame()->getSoundManager()->stopSound();
                    Game::instance().gotoSceneGame();
                }
            }
            else
            {
                replayText->setColor(glm::vec4(1, 1, 1, 1));
            }
        }
    }

}

void WinSymbol::render(ShaderProgram &program)
{
    ISceneNode::render(program);

    Camera *cam = Game::getCurrentSceneGame()->getCamera();

    glm::ivec2 centralPos = cam->getPosition() + glm::ivec2(Game::instance().getScreenWidth(), Game::instance().getScreenHeight())/2;

    glm::ivec2 lerpedPosition = getPosition() + glm::ivec2(glm::vec2(centralPos - getPosition()) * ( (scale-1.0f) / maxScale ));
    prepareModelViewMatrix(lerpedPosition - glm::ivec2( glm::vec2(winSprite->getSize()/2) * scale ),
                           glm::vec2(scale));
    winSprite->render();
}


