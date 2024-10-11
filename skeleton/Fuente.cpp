#include "Fuente.h"

Fuente::Fuente(PxVec3 pos, PxVec3 vel, int numP) : posIni(pos), velMedia(vel), numParticles(numP)
{
	posIni = Vector3(0, 0, 0);
	velMedia = Vector3(5, 40, 0);
	numParticles = 10;

}

void Fuente::ParticlesGen() {

	for (int i = 0; i < 20; i++) {
		Particle* particle = new Particle(posIni, velMedia, Vector3(0, 0, 0), 1);
		particle->SetAccel(Vector3(0, -10, 0));
		particlesVector.push_back(particle);
	}



}

void Fuente::Update(double t) {
	for each (Particle * particle in particlesVector)
	{
		particle->Integrate(t);

	}
}