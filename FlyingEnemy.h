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
        ATTACK = 2
    };

    void init(ShaderProgram &shaderProgram) override;
    void update(int deltaTime) override;
    void move(int deltaTime) override;

private:
    State state;
    int movTime;
};

#endif // FLYINGENEMY_H
