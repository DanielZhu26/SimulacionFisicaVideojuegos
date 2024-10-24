#pragma once
#include "Fuente.h"
#include <random>
class NormalPartGen : public Fuente
{
private:
	
	Vector3 meanVel; //Media
	Vector3 dtVel; //Desviacion tipica


public:
	NormalPartGen(Particle* p, float rate, Vector3 devV, float spawnRange, spawnDist sd)
		: Fuente(p, rate, spawnRange, sd), meanVel(p->getVelocity()), dtVel(devV) {}


	Particle* emitParticle() override;

};