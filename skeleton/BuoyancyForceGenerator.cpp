#include "BuoyancyForceGenerator.h"


BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float V, float d, Particle* liquid_particle) :
	_heigth(h), _volume(V), _liquid_density(d), _gravity(9.8), _liquid_particle(liquid_particle)
{
	type = 5;
}


BuoyancyForceGenerator::~BuoyancyForceGenerator()
{

}

void BuoyancyForceGenerator::updateF(Particle* p, double t)
{
	float h = p->getPos().y;
	float h0 = _liquid_particle->getPos().y;

	Vector3D<> f(0, 0, 0);
	float inmersed = 0.0;

	if (h - h0 > _heigth * 0.5) {
		inmersed = 0.0;  // El objeto está completamente fuera del líquido
	}
	else if (h0 - h > _heigth * 0.5) {
		inmersed = 1.0;  // El objeto está completamente sumergido
	}
	else {
		inmersed = (h0 - h) / _heigth + 0.5;  // El objeto está parcialmente sumergido
	}

	f.y = _liquid_density * _volume * inmersed * 9.8;

	p->ApplyForce(f);
}
