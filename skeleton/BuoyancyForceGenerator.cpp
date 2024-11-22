#include "BuoyancyForceGenerator.h"

void BuoyancyForceGenerator::updateF(Particle* p, double t)
{
	float h = p->getPos().y;
	float h0 = _liquid_particle->getPos().y;

	Vector3D<> f(0, 0, 0);
	float inmersed = 0.0;

	if (h - h0 > _heigth * 0.5)
	{
		inmersed = 0.0;
	}
	else if (h0 - h > _heigth * 0.5)
	{
		//Totally inmersed
		inmersed = 1.0;
	}
	else
	{
		inmersed = (h0 - h) / _heigth + 0.5;
	}

	f.y = _liquid_density * _volume * inmersed * 9.8;

	p->ApplyForce(f);
}
