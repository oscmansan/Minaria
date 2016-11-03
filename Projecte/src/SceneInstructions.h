#ifndef SCENEINSTRUCTIONS_H
#define SCENEINSTRUCTIONS_H

#include "Scene.h"
#include "SoundManager.h"

class SceneInstructions : public Scene
{
public:
    SceneInstructions();
    virtual ~SceneInstructions();

    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:
    Text *text1, *text2, *text3, *text4, *text5, *text6,
         *text7, *text8, *InstructionsText, *backText;
    Sprite *spriteBg;
    Texture textureMenuBg;

    SoundManager* soundManager = NULL;
};

#endif // SCENEINSTRUCTIONS_H
