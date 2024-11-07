#ifndef SPARKGEN_H
#define SPARKGEN_H

#include "Fuente.h"
#include <random>

class SparkGen : public Fuente
{
private:
    float force;

public:
    SparkGen(Vector3D<> pos, float force, ParticleSystem* sysS);
    ~SparkGen();

    void ParticleGen() override;
    Vector3D<> CalcRndPos();
};

#endif
