#ifndef SPARKGEN_H
#define SPARKGEN_H

#include "Fuente.h"
#include <random>

class SparkGen : public Fuente
{
private:
    float force;
    bool explosionTriggered = false;
    float explosionHeight;

public:
    SparkGen(Vector3D<> pos, float force, ParticleSystem* sysS, float lifetime);
    ~SparkGen();

    void ParticleGen() override;
    Vector3D<> CalcRndPos();
};

#endif
