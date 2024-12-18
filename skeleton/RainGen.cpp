#include "RainGen.h"


RainGen::RainGen(Vector3D<> pos, float rad, int force, ParticleSystem* sysR, float lifetime) :
	Fuente(pos, Vector3D<>(0, -1, 0), 0, 0, 0, sysR, lifetime), rad(rad), force(force)
{

}

RainGen::~RainGen()
{
}

void RainGen::ParticleGen()
{
	for (int i = 0; i < force; i++)
		systemRef->addParticle(CalcRndPos(),Vector3D<>(0, -1, 0), 1, 
		PxGeometryType::Enum::eSPHERE,0.2,physx::PxVec4(0.0, 0.0, 1.0, 1.0));
}

Vector3D<> RainGen::CalcRndPos()
{
	std::uniform_real_distribution<> uni_dist(-1, 1);
	std::uniform_real_distribution<> angle_dist(-3.14, 3.14);

	float rndRad = rad * sqrt(uni_dist(rnd));
	float rndAngle = angle_dist(rnd);

	float x = rndRad * cos(rndAngle);
	float z = rndRad * sin(rndAngle);

	Vector3D<> rndPos = {x + position.x, position.y, z + position.z};

	return rndPos;
}