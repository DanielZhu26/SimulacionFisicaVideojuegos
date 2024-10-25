#pragma once
#include "Vector3D.h"
#include <PxPhysicsAPI.h>


using namespace physx;
class RenderItem;

class Particle
{
public:
	Particle::Particle(Vector3D<> pos, Vector3D<> vel, const PxGeometryType::Enum& geoType = PxGeometryType::Enum::eSPHERE,
		float size = 0.5, const PxVec4& color = PxVec4(1.0, 1.0, 0.0, 1.0));
	~Particle();

	void integrate(double t);
	void decreaseLife(double t);

	//Getters
	double getLifeTime() { return lifeTime; };

	Vector3D<> getAccel() const { return acele; }
	Vector3D<> getVel() const { return velo; };
	Vector3D<> getPos() const { return Vector3D<>(trnasform->p.x, trnasform->p.y, trnasform->p.z); };

	//Setters
	void setAccel(Vector3D<> acel) { acele = acel; }
	void setVel(Vector3D<> vel) { velo = vel; }
	void setPos(Vector3D<> pos) { trnasform->p = PxVec3(pos.x, pos.y, pos.z); }

protected:

	RenderItem* renderItem;
	PxTransform* trnasform;

	Vector3D<> velo;
	Vector3D<> acele;

	double lifeTime;
	double damping;
	
};
