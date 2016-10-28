#ifndef SCENECREDITS_H
#define SCENECREDITS_H

#include "Scene.h"
#include "SoundManager.h"

class SceneCredits : public Scene
{
public:
    SceneCredits();
    virtual ~SceneCredits();

    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:
    Text *oscarText, *victorText, *creditsText, *backText;
    Sprite *spriteBg;
    Texture textureMenuBg;

    SoundManager* soundManager = NULL;
};

#endif // SCENECREDITS_H
