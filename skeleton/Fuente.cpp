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
	partRef = new Particle(pos, dir * vel, PxGeometryType::Enum::eSPHERE, 1, PxVec4(0.0, 0.0, 27.0, 1.0));

	std::random_device rd;
	rnd = std::mt19937(rd());
}

Fuente::~Fuente()
{

}