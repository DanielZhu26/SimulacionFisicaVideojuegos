#include "SparkGen2.h"

SparkGen2::SparkGen2(Vector3D<> pos, float force, ParticleSystem* sysS, float lifetime) :
    Fuente(pos, Vector3D<>(0, 1, 0), 0, 0, 0, sysS, lifetime), force(force)
{


}

SparkGen2::~SparkGen2()
{
}

void SparkGen2::ParticleGen()
{
    for (int i = 0; i < force; i++) {
        Vector3D<> rndVel = Vector3D<>(rnd() % 2 - 1, rnd() % 2, rnd() % 2 - 1) * 2.0f;
        systemRef->addParticle(CalcRndPos(), rndVel * 10, 1, PxGeometryType::Enum::eSPHERE, 0.1, PxVec4(1.0, 0.5, 0.0, 1.0));
    }
}

Vector3D<> SparkGen2::CalcRndPos()
{
    std::uniform_real_distribution<> uni_dist(-1, 1);

    float x = uni_dist(rnd) * force;
    float y = uni_dist(rnd) * force;
    float z = uni_dist(rnd) * force;


    return Vector3D<>(x + position.x, y + position.y, z + position.z);

}