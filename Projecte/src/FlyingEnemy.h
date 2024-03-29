#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H

#include "Enemy.h"

class FlyingEnemy : public Enemy
{
public:
    FlyingEnemy(int posx);
    ~FlyingEnemy();

    enum State {
        PATROL = 0,
        CHASE  = 1,
        ATTACK = 2,
    };

    void init() override;
    void update(int deltaTime) override;
    void move(int deltaTime) override;

private:
    State state;
    glm::ivec2 attackPosStart;
    glm::ivec2 attackPosEnd;
    int origx;
    int bombTimer;
};

#endif // FLYINGENEMY_H
