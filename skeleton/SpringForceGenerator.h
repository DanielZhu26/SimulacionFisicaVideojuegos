#pragma once
#include "ForceGen.h"

class SpringForceGenerator : public ForceGen
{
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);

	virtual void updateF(Particle* particle, double t) override;

	inline void setK(double k) { _k = k; };

	virtual ~SpringForceGenerator() {}
protected:
	double _k;	// Elastic Coeff
	double _resting_length;
	Particle* _other;
};