#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <cmath>
#include <list>
#include "ParticleSystem.h"
 
using namespace physx;
using namespace std;
class ParticleSystem;
class Particle
{
public:
	Particle(PxVec3 pos, PxVec3 velo, PxVec3 acel, double masa, double lifeT);
	~Particle();

	void Integrate(double t);

	void SetAccel(PxVec3 newAcel);
	void SetVel(PxVec3 newVel);

	void update(double t, ParticleSystem& sys);

	double getLifeTime() {
		return lifeTime;
	}
	void setLifeTime(float t) { lifeTime = t; }

	void setIterator(std::list<Particle*>::iterator it) {
		part_it = it;
	}
	std::list<Particle*>::iterator getIterator() const {
		return part_it;
	}

	bool isInside(Vector3 const& v, float radio);

private:
	PxVec3 velo;
	PxVec3 acele;
	PxVec3 pose;

	double mass;
	double livedTime;
	double lifeTime;

	PxTransform* transform = nullptr;

	double damping;

	RenderItem* renderItem = nullptr;

	list<Particle*>::iterator part_it;


};



