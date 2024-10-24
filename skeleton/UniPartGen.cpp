#include "UniPartGen.h"

Particle* UniPartGen::emitParticle()
{
    std::uniform_real_distribution<float> distX(minVelocity.x, maxVelocity.x);
    std::uniform_real_distribution<float> distY(minVelocity.y, maxVelocity.y);
    std::uniform_real_distribution<float> distZ(minVelocity.z, maxVelocity.z);

    Vector3 randomVelocity(distX(randm), distY(randm), distZ(randm));

    Particle* newParticle = new Particle(particle);

    newParticle->SetVel(randomVelocity);
    newParticle->setPosition(calculatePosition());

    return newParticle;
}