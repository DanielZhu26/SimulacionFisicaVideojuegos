#pragma once
#include "Vector3D.h"
#include <PxPhysicsAPI.h>


using namespace physx;
class RenderItem;

class Particle
{
public:
	Particle(PxVec3 pos, PxVec3 vel, PxVec3 acel);
	Particle(Vector3D<> pos, Vector3D<> vel, Vector3D<> acel, float mass = 1.0f);
	Particle::Particle(Vector3D<> pos, Vector3D<> vel, const PxGeometryType::Enum& geoType = PxGeometryType::Enum::eSPHERE,
		float size = 0.5, const PxVec4& color = PxVec4(1.0, 1.0, 0.0, 1.0));
	~Particle();

	void semiIntegrate(double t);
	void Integrate(double t);
	void decreaseLife(double t);

	//Getters
	double getLifeTime() { return lifeTime; }

	Vector3D<> getAccel() const { return acele; }
	Vector3D<> getVel() const { return velo; }
	Vector3D<> getPos() const { return Vector3D<>(transform->p.x, transform->p.y, transform->p.z); }

	float getMass() const { return mass; }

	//Setters
	void setAccel(Vector3D<> acel) { acele = acel; }
	void setVel(Vector3D<> vel) { velo = vel; }
	void setPos(Vector3D<> pos) { transform->p = PxVec3(pos.x, pos.y, pos.z); }
	void setAcel(PxVec3 newAcel) { accel = newAcel; }

protected:

	RenderItem* renderItem;
	PxTransform* transform;

	Vector3D<> velo;
	Vector3D<> acele;
	Vector3D<> pose;

	PxVec3 speed;
	PxVec3 accel;
	PxVec3 posit;

	double lifeTime;
	double damping = 0.99;

	float mass;
	
};
