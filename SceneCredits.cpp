#include "SceneCredits.h"

#include "Game.h"

SceneCredits::SceneCredits()
{
}

SceneCredits::~SceneCredits()
{
    delete soundManager;
}


void SceneCredits::init()
{
    Scene::init();

    textureMenuBg.loadFromFile("images/creditsBG.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteBg = Sprite::createSprite(glm::ivec2(Game::getScreenWidth(), Game::getScreenHeight()), glm::vec2(1.0f), &textureMenuBg, &texProgram);

    creditsText = createText("Credits", glm::ivec2(210, 100), 45);
    oscarText = createText("Oscar Manas", glm::ivec2(180, 300), 25);
    victorText = createText("Victor Anton", glm::ivec2(160, 350), 25);
    backText = createText("Back", glm::ivec2(50, 500), 25);

    creditsText->centerHorizontally();
    oscarText->centerHorizontally();
    victorText->centerHorizontally();

    backText->setColor(glm::vec4(1,1,1,1));

    soundManager = new SoundManager();
    soundManager->setVolume(60.f);
}

void SceneCredits::update(int deltaTime)
{
    Scene::update(deltaTime);

    Game *game = &(Game::instance());

    if (oscarText->getBoundingRect().contains(game->getMousePosScreen()))
    { oscarText->setText("OSCAR GAY", 40); soundManager->playSound("../sounds/Wilhelm_Scream.ogg"); } else { oscarText->setText("Oscar Manas", 25); }
    oscarText->centerHorizontally();

    if (victorText->getBoundingRect().contains(game->getMousePosScreen()))
    { victorText->setText("HABLAS MI IDIOMA?", 30); soundManager->playSound("../sounds/Wilhelm_Scream.ogg"); } else { victorText->setText("Victor Anton", 25); }
    victorText->centerHorizontally();

    if (backText->getBoundingRect().contains(game->getMousePosScreen()))
    {
        backText->setColor(glm::vec4(1,1,0,1));
        if (game->getMouseLeftButtonDown())
        {
            game->gotoSceneMenu();
        }
    }
    else
    {
        backText->setColor(glm::vec4(1,1,1,1));
    }
}

void SceneCredits::render()
{
    spriteBg->render();
}
