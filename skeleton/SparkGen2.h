#pragma once
#include "Fuente.h"
#include <random>

class SparkGen2 : public Fuente
{
private:
    float force;



public:
    SparkGen2(Vector3D<> pos, float force, ParticleSystem* sysS, float lifetime);
    ~SparkGen2();

    void ParticleGen() override;
    Vector3D<> CalcRndPos();
};