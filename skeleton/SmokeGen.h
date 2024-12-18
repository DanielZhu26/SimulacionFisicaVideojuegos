#ifndef SMOKECGEN_H
#define SMOKECGEN_H

#include "Fuente.h"
#include <random>

class SmokeGen : public Fuente
{
private:
    int force;

public:
    SmokeGen(Vector3D<> pos, int force, ParticleSystem* sysS, float lifetime);
    ~SmokeGen();

    void ParticleGen() override;
    Vector3D<> CalcRndPos();
};

#endif
