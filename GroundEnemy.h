#ifndef GROUNDENEMY_H
#define GROUNDENEMY_H

#include "Enemy.h"

class GroundEnemy : public Enemy
{
public:
    GroundEnemy();
    ~GroundEnemy();

    enum State {
        PATROL = 0,
        CHASE  = 1,
        ATTACK = 2
    };

    void init(ShaderProgram &shaderProgram) override;
    void update(int deltaTime) override;
    void move(int deltaTime) override;

private:
    State state;
};

#endif // GROUNDENEMY_H
