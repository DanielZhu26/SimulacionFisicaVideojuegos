#pragma once

#include "ForceGen.h"

class BuoyancyForceGenerator : public ForceGen
{
public:
	BuoyancyForceGenerator(float h, float V, float d);

	virtual void updateF(Particle* p, double t);

	virtual ~BuoyancyForceGenerator();

protected:
	float _heigth;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle;
};

