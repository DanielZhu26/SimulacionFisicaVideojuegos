#include "NormalPartGen.h"
#include <limits>
#include <cfloat>

using namespace std;

NormalPartGen::NormalPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel, ParticleSystem* sysR, float lifetime) :
    Fuente(pos, dir, vel, deltAngle, deltVel, sysR, lifetime)
{
    if (deltAngle != 0.0)
        gaussianDistAngle = std::normal_distribution<>(0, deltAngle * (3.14 / 180));
    else
        gaussianDistAngle = std::normal_distribution<>(0, FLT_MIN);


    if (deltVel != 0.0)
        gaussianDistSpeed = std::normal_distribution<>(0, deltVel);
    else
        gaussianDistSpeed = std::normal_distribution<>(0, FLT_MIN);
}


NormalPartGen::~NormalPartGen()
{

}

void NormalPartGen::ParticleGen()
{
    systemRef->addParticle(position, CalculateRndDir() * CalcRndVel(), 1, PxGeometryType::Enum::eSPHERE, 0.5, PxVec4(1.0, 1.0, 0.0, 1.0));
   
}

Vector3D<> NormalPartGen::CalculateRndDir()
{
    float rndAngle = gaussianDistAngle(rnd); 

    float aunxAngle = gaussianDistAngle(rnd) * 3.14;

    float sinAngle = std::sin(rndAngle);
    float cosAngle = std::cos(rndAngle);

    Vector3D<> rndVec = {sinAngle * cos(aunxAngle), sinAngle * sin(aunxAngle), cosAngle
    };

    Vector3D<> rndDir = { direction.x * cosAngle + rndVec.x, direction.y * cosAngle + rndVec.y, direction.z * cosAngle + rndVec.z
    };

    rndDir.Normalize();

    return rndDir;
}

float NormalPartGen::CalcRndVel()
{
    float rndVel = gaussianDistSpeed(rnd);
    float resVel = rndVel + vel;

    return resVel;
}