#include "SmokeGen.h"

SmokeGen::SmokeGen(Vector3D<> pos, int force, ParticleSystem* sysS) :
    Fuente(pos, Vector3D<>(0, 1, 0), 0, 0, 0, sysS), force(force)
{
}

SmokeGen::~SmokeGen()
{
}

void SmokeGen::ParticleGen()
{
    for (int i = 0; i < force; i++) {
        // Ajustamos la velocidad para que las partículas se eleven hacia arriba lentamente y se dispersan suavemente
        Vector3D<> rndVel = Vector3D<>(rnd() % 2 - 1, 50 , rnd() % 2 - 1); 
        systemRef->addParticle(CalcRndPos(), rndVel , PxGeometryType::Enum::eSPHERE, 5, PxVec4(0.9, 0.9, 0.9, 1));
    }
}

Vector3D<> SmokeGen::CalcRndPos()
{
    std::uniform_real_distribution<> uni_dist(-1, 1);

    float x = uni_dist(rnd) * 20;
    float y = position.y;
    float z = uni_dist(rnd) * 20;

    return Vector3D<>(x + position.x, y, z + position.z);
}
