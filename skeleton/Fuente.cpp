#include "Fuente.h"
#include "ParticleSystem.h"

void Fuente::update(double t, ParticleSystem& partSys) {
    // Acumula el tiempo
    counter += t;

    // Particulas a emitir
    int particlesToEmit = static_cast<int>(counter * genRate);

    for (int i = 0; i < particlesToEmit; ++i) {
        Particle* newParticle = emitParticle();

        if (newParticle) {
            partSys.addParticle(newParticle);
            newParticle->setLifeTime(partSys.getParticleLifeTime());
        }
    }

    counter -= particlesToEmit / genRate;
}