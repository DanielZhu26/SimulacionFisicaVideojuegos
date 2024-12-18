#include "Fuente.h"
#include <random>

Fuente::Fuente(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel, ParticleSystem* sysR, float lifetime) :
	id(-1),
	position(pos),
	direction(dir),
	vel(vel),
	deltAngle(deltAngle),
	deltVel(deltVel),
	systemRef(sysR),
	life(lifetime)
{
	partRef = new Particle(pos, dir * vel, 0, PxGeometryType::Enum::eSPHERE, 0.1, PxVec4(0.0, 0.0, 0.0, 0.0));

	std::random_device rd;
	rnd = std::mt19937(rd());
}

Fuente::~Fuente()
{
	delete partRef;
}