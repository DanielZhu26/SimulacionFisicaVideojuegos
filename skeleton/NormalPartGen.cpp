#include "NormalPartGen.h"

Particle* NormalPartGen::emitParticle()
{
    std::normal_distribution<float> distX(meanVel.x, dtVel.x);
    std::normal_distribution<float> distY(meanVel.y, dtVel.y);
    std::normal_distribution<float> distZ(meanVel.z, dtVel.z);


    Vector3 randomVelocity(distX(randm), distY(randm), distZ(randm));

    Particle* newParticle = new Particle(particle);

    newParticle->SetVel(randomVelocity);
    newParticle->setPosition(calculatePosition());

    return newParticle;
}