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
	Particle(PxVec3 pos, PxVec3 velo, PxVec3 acel, double masa);
	~Particle();

	void Integrate(double t);

	void SetAccel(PxVec3 newAcel);
	void SetVel(PxVec3 newVel);

private:
	PxVec3 velo;
	PxVec3 acele;
	PxVec3 pose;

	double mass;

	PxTransform* transform = nullptr;

	double damping;

	RenderItem* renderItem = nullptr;


};



