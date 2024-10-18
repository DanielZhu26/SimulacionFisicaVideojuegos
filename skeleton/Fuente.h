#pragma once
#include "Particle.h"

#include <random>
class ParticleSystem;
class Fuente
{
protected:
	std::mt19937 randm;
	float genRate;
	Vector3 pos;
	Vector3 direction;
    float counter = 0.0f;

public:
	Fuente(Vector3 pos, float rate): pos(pos), genRate(rate) {
		std::random_device rd;
		randm.seed(rd());
	}

	void update(double t, ParticleSystem& partSys);

	virtual Particle* emitParticle() = 0;

	float getGenRate() const { return genRate; }

};
