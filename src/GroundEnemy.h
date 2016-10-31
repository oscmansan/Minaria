#ifndef GROUNDENEMY_H
#define GROUNDENEMY_H

#include "Enemy.h"

class GroundEnemy : public Enemy
{
public:
    GroundEnemy(int posx);
    ~GroundEnemy();

    enum State {
        PATROL = 0,
        CHASE  = 1,
        ATTACK = 2
    };

    void init() override;
    void update(int deltaTime) override;
    void move(int deltaTime) override;

private:
    State state;

    int origx;
};

#endif // GROUNDENEMY_H
