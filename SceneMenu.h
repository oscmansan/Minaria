#ifndef SCENEMENU_H
#define SCENEMENU_H

#include "Scene.h"
#include "SoundManager.h"

class SceneMenu : public Scene
{
public:
    SceneMenu();
    virtual ~SceneMenu();

    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:
    const glm::vec4 IdleColor = glm::vec4(1, 1, 1, 1);
    const glm::vec4 OverColor = glm::vec4(1, 0.7, 0, 1);

    Text *title, *playText, *instructionsText, *creditsText;

    Sprite *spriteBg;
    Texture textureMenuBg;

    SoundManager* soundManager = NULL;
};

#endif // SCENEMENU_H
