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

    textureMenuBg.loadFromFile("images/menuBg.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteBg = Sprite::createSprite(glm::ivec2(Game::getScreenWidth(), Game::getScreenHeight()), glm::vec2(1.0f), &textureMenuBg, &texProgram);

    Text *title = createText("Minaria", glm::ivec2(50, 80), 50);
    title->setColor(glm::vec4(1,1,0,1));
    title->centerHorizontally();

    playText         = createText("Play game", glm::ivec2(50, 300), 25);
    instructionsText = createText("Instructions", glm::ivec2(50, 350), 25);
    creditsText      = createText("Credits", glm::ivec2(50, 400), 25);
    playText->centerHorizontally();
    instructionsText->centerHorizontally();
    creditsText->centerHorizontally();
}

void SceneMenu::update(int deltaTime)
{
    Scene::update(deltaTime);

    Game *game = &(Game::instance());
    if (playText->getBoundingRect().contains(game->getMousePosScreen()))
    {
        playText->setColor(OverColor);
        if (game->getMouseLeftButtonDown())
        {
            game->gotoSceneGame();
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
