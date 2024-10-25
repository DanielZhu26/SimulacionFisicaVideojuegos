#include "NormalPartGen.h"
#include <limits>


NormalPartGen::NormalPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel, ParticleSystem* sysR) :
    Fuente(pos, dir, vel, deltAngle, deltVel, sysR)
{
    if (deltAngle != 0.0)
        gaussianDistAngle = std::normal_distribution<>(0, deltAngle * (3.14 / 180));
    else
        gaussianDistAngle = std::normal_distribution<>(0, std::numeric_limits<float>::min());


    if (deltVel != 0.0)
        gaussianDistSpeed = std::normal_distribution<>(0, deltVel);
    else
        gaussianDistSpeed = std::normal_distribution<>(0, std::numeric_limits<float>::min());
}


NormalPartGen::~NormalPartGen()
{

}

void NormalPartGen::ParticleGen()
{
    systemRef->addParticle(position, CalculateRndDir() * CalcRndVel(), PxGeometryType::Enum::eSPHERE, 0.5, PxVec4(1.0, 1.0, 0.0, 1.0));
}

Vector3D<> NormalPartGen::CalculateRndDir()
{
    // Genera un ángulo aleatorio entre -angleDelta y angleDelta (en radianes)
    float randomAngle = gaussianDistAngle(rnd); // Ángulo en radianes

    // Genera un ángulo aleatorio en el plano (-π, π)
    float phi = gaussianDistAngle(rnd) * 3.14;

    // Calcula las coordenadas del nuevo vector
    float sinRandomAngle = std::sin(randomAngle);
    float cosRandomAngle = std::cos(randomAngle);

    // Vector en coordenadas esféricas
    Vector3D<> randomVector = {
        sinRandomAngle * std::cos(phi),
        sinRandomAngle * std::sin(phi),
        cosRandomAngle
    };

    // Combina el nuevo vector con la dirección
    // Proyección en la dirección del vector
    Vector3D<> result = {
        direction.x * cosRandomAngle + randomVector.x,
        direction.y * cosRandomAngle + randomVector.y,
        direction.z * cosRandomAngle + randomVector.z
    };

    // Normaliza el resultado
    result.Normalize();

    return result;
}

float NormalPartGen::CalcRndVel()
{
    // Genera una velocidad aleatoria entre -speedDelta y speedDelta
    float randomSpeed = gaussianDistSpeed(rnd);

    // Añade la nueva velocidad aleatoria a la original
    float result = randomSpeed + vel;

    return result;
}