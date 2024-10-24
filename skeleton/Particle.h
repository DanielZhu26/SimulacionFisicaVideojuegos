#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <cmath>
#include <list>

 
using namespace physx;
using namespace std;
class ParticleSystem;
class Particle
{
public:
	Particle(PxVec3 pos, PxVec3 velo, PxVec3 acel, double masa, double lifeT);
	Particle(Vector3 pos, Vector3 vel, Vector3 acel = { 0,0,0 });
	virtual ~Particle();

	void Init(Vector3 pos, Vector3 vel, Vector3 acel = Vector3(0, -10, 0));

	void Integrate(double t);

	void SetAccel(PxVec3 newAcel);
	

	Vector3 getVelocity() const {
		return velo;
	}

	void SetVel(PxVec3 newVel);


	Vector3 getPosition() const {
		return transform.p;
	}

	void setPosition(Vector3 p) {
		transform.p = p;
	}

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

	PxTransform transform;

	double damping;

	RenderItem* renderItem = nullptr;

	list<Particle*>::iterator part_it;


};



