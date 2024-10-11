#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <cmath>
#include "Particle.h"

class Fuente
{
public:
	Fuente(PxVec3 pos, PxVec3 vel, int numPart);
	~Fuente();


	void ParticlesGen();
	void Update(double t);

private:

	vector<Particle*> particlesVector;
	PxVec3 posIni;
	PxVec3 velMedia;

	int numParticles;

	PxTransform* transform = nullptr;

	double damping;

	RenderItem* renderItem = nullptr;


};

