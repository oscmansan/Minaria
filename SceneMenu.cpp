#include "SceneMenu.h"

#include "Game.h"

SceneMenu::SceneMenu()
{
}

SceneMenu::~SceneMenu()
{
    delete spriteBg;
}

void SceneMenu::init()
{
    Scene::init();

    textureMenuBg.loadFromFile("images/menuBG.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteBg = Sprite::createSprite(glm::ivec2(Game::getScreenWidth(), Game::getScreenHeight()), glm::vec2(1.0f), &textureMenuBg, &texProgram);

    //Text *title = createText("Minaria", glm::ivec2(50, 80), 50);
    //title->setColor(glm::vec4(1,1,1,1));
    //title->centerHorizontally();

    title            = createText("MINARIA", glm::ivec2(0, 50), 60);
    playText         = createText("Play game", glm::ivec2(50, 300), 25);
    instructionsText = createText("Instructions", glm::ivec2(50, 350), 25);
    creditsText      = createText("Credits", glm::ivec2(50, 400), 25);
    title->centerHorizontally();
    playText->centerHorizontally();
    instructionsText->centerHorizontally();
    creditsText->centerHorizontally();

    soundManager = new SoundManager();
    soundManager->setVolume(60.f);
    soundManager->playMusic("../sounds/meadow.ogg");
}

void SceneMenu::update(int deltaTime)
{
    Scene::update(deltaTime);

    static int timer = 0;
    timer += deltaTime;
    float sizeFactor = abs(sin(float(timer) / 1000.0f * 5.0f));
    title->setText("MINARIA", 5 * sizeFactor + 60);
    title->centerHorizontally();
    title->setColor(glm::vec4(1) * sizeFactor * 0.5f + 0.5f);

    Game *game = &(Game::instance());
    if (playText->getBoundingRect().contains(game->getMousePosScreen()))
    {
        playText->setColor(OverColor);
        if (game->getMouseLeftButtonDown())
        {
            soundManager->stopMusic();
            game->gotoSceneGame();
            return;
        }
    }
    else
    {
        playText->setColor(IdleColor);
    }

    if (instructionsText->getBoundingRect().contains(game->getMousePosScreen()))
    {
        instructionsText->setColor(OverColor);
        if (game->getMouseLeftButtonDown())
        {

        }
    }
    else
    {
        instructionsText->setColor(IdleColor);
    }

    if (creditsText->getBoundingRect().contains(game->getMousePosScreen()))
    {
        creditsText->setColor(OverColor);
        if (game->getMouseLeftButtonDown())
        {
            game->gotoSceneCredits();
            return;
        }
    }
    else
    {
        creditsText->setColor(IdleColor);
    }

}

void SceneMenu::render()
{
    spriteBg->render();
}
