#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <cmath>
 
using namespace physx;
using namespace std;
class Particle
{
public:
	Particle(PxVec3 pos, PxVec3 velo, PxVec3 acel);
	~Particle();

	void Integrate(double t);

private:
	PxVec3 velo;
	PxVec3 acele;
	PxVec3 pose;

	PxTransform* transform = nullptr;

	double damping;

	RenderItem* renderItem = nullptr;


};



