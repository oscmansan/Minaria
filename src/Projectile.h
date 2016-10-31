#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Sprite.h"
#include "ISceneNode.h"

class Projectile : public ISceneNode
{
public:
    Projectile();
    virtual ~Projectile();

    void update(int deltaTime) override;
    void render(ShaderProgram &program) override;

    void setVelocity(const glm::vec2 &vel);
    glm::ivec2 getSize() const override;

    void explode();

private:
    int explosionRadius = 96;
    int damageInCenter = 3;
    glm::vec2 velocity;
    float rotSpeed = 1;
    bool grounded = false;

    static Texture *texture;
    Sprite *sprite = NULL;
};

#endif // PROJECTILE_H
