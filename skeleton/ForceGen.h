#pragma once

#include <list>
#include "Particle.h"

class ForceGen {
public:
    ForceGen() {};

    ~ForceGen() {};

    virtual void updateF(Particle* p, double t) = 0;

    int getType() { return type; }

protected:
    int type;
    //wind 1, gravity 2, explosion 3, tornado 4
};