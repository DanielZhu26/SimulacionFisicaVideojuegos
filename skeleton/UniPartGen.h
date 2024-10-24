#pragma once
#include "Fuente.h"
#include <random>

class UniPartGen : public Fuente
{
private:
    Vector3 minVelocity;
    Vector3 maxVelocity;

public:
    UniPartGen(Particle* p, float rate, float range, float spawnRange, spawnDist sd)
        : Fuente(p, rate, spawnRange, sd)
    {
        Vector3 vel = p->getVelocity();
        Vector3 dev = Vector3(range, range, range);
        minVelocity = vel - dev;
        maxVelocity = vel + dev;
    }

    Particle* emitParticle() override;
};

