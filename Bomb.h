#ifndef BOMB_H
#define BOMB_H

#include "Sprite.h"
#include "ISceneNode.h"

class Bomb : public ISceneNode
{
public:
    Bomb();
    virtual ~Bomb();

    void update(int deltaTime) override;
    void render(ShaderProgram &program) override;

    void setVelocity(const glm::vec2 &vel);
    glm::ivec2 getSize() const override;

    void explode();

private:
    int explosionRadius = 1;
    glm::vec2 velocity;
    float rotSpeed = 1;
    bool grounded = false;

    static Texture *bombTexture;
    Sprite *sprite = NULL;
};

#endif // BOMB_H
