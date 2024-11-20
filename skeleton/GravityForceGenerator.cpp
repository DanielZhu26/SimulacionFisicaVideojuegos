#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(Vector3D<> gravityacel) :
	ForceGen(),
	gravityAcel(gravityacel)
{

}

GravityForceGenerator::~GravityForceGenerator()
{

}

void GravityForceGenerator::updateF(Particle* p, double t)
{
	p->ApplyForce(gravityAcel * t * p->getMass());
}