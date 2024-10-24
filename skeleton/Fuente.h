#pragma once
#include "Particle.h"

#include <random>
class ParticleSystem;

enum spawnDist {
	UNIFORM_SD,
	NORMAL_SD
};


class Fuente
{
protected:
	std::mt19937 randm;
	float genRate; //Part. por segundo
	float genRange;

    float counter = 0.0f;

	Particle particle;
	spawnDist sd;

public:
	Fuente(Particle* p, float rate, float range, spawnDist sd)
		: particle(*p), genRate(rate), genRange(range), sd(sd) {
		std::random_device rd;
		randm.seed(rd());
	}

	void update(double t, ParticleSystem& partSys);

	virtual Particle* emitParticle() = 0;

	float getGenRate() const { return genRate; }

	Vector3 calculatePosition();

};
