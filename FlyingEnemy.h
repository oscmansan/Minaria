#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H

#include "Enemy.h"

class FlyingEnemy : public Enemy
{
public:
    FlyingEnemy();
    ~FlyingEnemy();

    enum State {
        PATROL = 0,
        CHASE  = 1,
        ATTACK_DOWN = 2,
        ATTACK_UP = 3
    };

    void init() override;
    void update(int deltaTime) override;
    void move(int deltaTime) override;

private:
    State state;
    glm::ivec2 attackPosStart;
    glm::ivec2 attackPosEnd;

    void randomFly();
};

#endif // FLYINGENEMY_H
