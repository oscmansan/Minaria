#include "SceneInstructions.h"

#include "Game.h"

SceneInstructions::SceneInstructions()
{
}

SceneInstructions::~SceneInstructions()
{
    delete soundManager;
}


void SceneInstructions::init()
{
    Scene::init();

    textureMenuBg.loadFromFile("images/creditsBG.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spriteBg = Sprite::createSprite(glm::ivec2(Game::getScreenWidth(), Game::getScreenHeight()), glm::vec2(1.0f), &textureMenuBg, &texProgram);

    InstructionsText = createText("Instructions", glm::ivec2(0, 40), 45);
    text1= createText("Controls",                            glm::ivec2(50, 115), 25);
    text2 = createText("  * A-D to move",                    glm::ivec2(50, 160), 15);
    text3 = createText("  * W-Z to jump",                    glm::ivec2(50, 190), 15);
    text4 = createText("  * Mouse to aim and use items",     glm::ivec2(50, 220), 15);
    text4 = createText("  * 1..7 or Q-E or mouse to select", glm::ivec2(50, 250), 15);
    text5 = createText("    in the Inventory",               glm::ivec2(50, 280), 15);
    text6 = createText("Tips", glm::ivec2(50, 330), 25);
    text7 = createText("  * Use the sword and bombs to fight the enemies", glm::ivec2(50, 375), 15);
    text8 = createText("  * You can not recover health...stay alert!", glm::ivec2(50, 405), 15);
    backText = createText("Back", glm::ivec2(50, 500), 25);

    InstructionsText->centerHorizontally();

    backText->setColor(glm::vec4(1,1,1,1));

    soundManager = new SoundManager();
    soundManager->setVolume(60.f);
}

void SceneInstructions::update(int deltaTime)
{
    Scene::update(deltaTime);

    Game *game = &(Game::instance());

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

void SceneInstructions::render()
{
    spriteBg->render();
}
