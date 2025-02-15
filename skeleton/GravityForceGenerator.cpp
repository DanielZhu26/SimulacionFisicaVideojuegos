#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(Vector3D<> gravityacel) :
	ForceGen(),
	gravityAcel(gravityacel)
{
	type = 2;
}

GravityForceGenerator::~GravityForceGenerator()
{

}

void GravityForceGenerator::updateF(Particle* p, double t)
{
	p->ApplyForce(gravityAcel * t * p->getMass());
}