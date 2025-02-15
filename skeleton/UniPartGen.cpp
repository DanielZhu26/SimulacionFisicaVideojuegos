﻿#include "UniPartGen.h"
#include <cmath>
#include <array>
#include <random>


using namespace std;
using namespace physx;

UniPartGen::UniPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAng, float deltVel, ParticleSystem* sys, float lifetime)
    :Fuente(pos, dir, vel, deltAng, deltVel, sys, lifetime)
{

}


UniPartGen::~UniPartGen()
{

}

void UniPartGen::ParticleGen()
{
    systemRef->addParticle(position, CalculateRndDir() * CalcRndVel(), 1, physx::PxGeometryType::Enum::eSPHERE, 0.3, physx::PxVec4(1.0, 0.5, 0.0, 1.0));
}

Vector3D<> UniPartGen::CalculateRndDir()
{
    float rndAngle = deltAngle * (3.14 / 180) * dist_uniforme(rnd); 

    float auxAngle = dist_uniforme(rnd) * 3.14;

    // Calcula las coordenadas del nuevo vector
    float sinAngle = sin(rndAngle);
    float cosAngle = cos(rndAngle);

    Vector3D<> rndVec = {sinAngle * cos(auxAngle), sinAngle * sin(auxAngle), cosAngle};

    Vector3D<> rndDir = {direction.x * cosAngle + rndVec.x, direction.y * cosAngle + rndVec.y, direction.z * cosAngle + rndVec.z};

    rndDir.Normalize();

    return rndDir;
}

float UniPartGen::CalcRndVel()
{
    float rndVel = deltVel * dist_uniforme(rnd);
    float resVel = rndVel + vel;

    return resVel;
}