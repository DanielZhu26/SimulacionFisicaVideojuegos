#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other)
{
	_k = k;
	_resting_length = resting_length;
	_other = other;
}

void SpringForceGenerator::updateF(Particle* particle, double t)
{
	// Particle" is the particle to apply the force
	Vector3D<> relative_pos_vector = _other->getPos() - particle->getPos();

	float length = relative_pos_vector.getMagnitude();
	float deltaX = length - _resting_length;

	Vector3D<> force = relative_pos_vector.GetNormalized() * deltaX * _k;

	particle->ApplyForce(force * t);
}
