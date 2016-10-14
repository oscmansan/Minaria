#ifndef SCENECREDITS_H
#define SCENECREDITS_H

#include "Scene.h"

class SceneCredits : public Scene
{
public:
    SceneCredits();

    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:
    Text *oscarText, *victorText, *creditsText, *backText;
};

#endif // SCENECREDITS_H
