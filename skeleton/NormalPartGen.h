#pragma once
#include "Fuente.h"
#include <random>
class NormalPartGen : public Fuente
{
private:
	//	Velocidad media para distribucion
	Vector3 meanVelocity;
	//	Desviacion tipica para distribucion
	Vector3 devVelocity;

public:
	NormalPartGen(Vector3 pos, float rate, Vector3 meanV, Vector3 devV)
		: Fuente(pos, rate), meanVelocity(meanV), devVelocity(devV) {}

	/**
	*	Genera particulas a partir de una distribucion normal
	*/
	Particle* emitParticle() override;

};