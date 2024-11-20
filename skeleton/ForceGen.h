#pragma once

#include <list>
#include "Particle.h"

class ForceGen {
public:
    ForceGen() {};

    ~ForceGen() {};

    virtual void updateF(Particle* p, double t) = 0;
};