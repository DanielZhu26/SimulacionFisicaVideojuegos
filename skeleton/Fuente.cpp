#include "Fuente.h"
#include <random>

Fuente::Fuente(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel, ParticleSystem* sysR) :
	id(-1),
	position(pos),
	direction(dir),
	vel(vel),
	deltAngle(deltAngle),
	deltVel(deltVel),
	systemRef(sysR)
{
	partRef = new Particle(pos, dir * vel, 1, PxGeometryType::Enum::eSPHERE, 0.1, PxVec4(1.0, 0.0, 0.0, 0.0));

	std::random_device rd;
	rnd = std::mt19937(rd());
}

Fuente::~Fuente()
{

}