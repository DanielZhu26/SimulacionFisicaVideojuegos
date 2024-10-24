#include "Fuente.h"
#include "ParticleSystem.h"

void Fuente::update(double t, ParticleSystem& partSys) {
    // Acumula el tiempo
    counter += t;

    int particles = static_cast<int>(counter * genRate);

    for (int i = 0; i < particles; ++i) {
        Particle* newParticle = emitParticle();

        if (newParticle) {
            partSys.addParticle(newParticle);
            newParticle->setLifeTime(partSys.getParticleLifeTime());
        }
    }

    counter -= particles / genRate;
}

Vector3 Fuente::calculatePosition()
{
    Vector3 modPos = particle.getPosition();
    Vector3 endPos;

    if (sd == UNIFORM_SD) {

        std::uniform_real_distribution<float> distX(modPos.x - genRange, modPos.x + genRange);
        std::uniform_real_distribution<float> distY(modPos.y - genRange, modPos.y + genRange);
        std::uniform_real_distribution<float> distZ(modPos.z - genRange, modPos.z + genRange);
        endPos = Vector3(distX(randm), distY(randm), distZ(randm));
    }
    else if (sd == NORMAL_SD) {

        Vector3 dev = { genRange, genRange, genRange };
        std::normal_distribution<float> distX(modPos.x, genRange);
        std::normal_distribution<float> distY(modPos.y, genRange);
        std::normal_distribution<float> distZ(modPos.z, genRange);
        endPos = Vector3(distX(randm), distY(randm), distZ(randm));
    }
    return endPos;
}