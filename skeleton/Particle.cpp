#include "Particle.h"

#include "RenderUtils.hpp"
#include <cmath>

using namespace physx;

Particle::Particle(Vector3D<> pos, Vector3D<> vel, const PxGeometryType::Enum& geoType, float size, const PxVec4& color)
{
	trnasform = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	velo = vel;
	acele = Vector3D<>();
	damping = 1;
	PxShape* shape = nullptr;
	lifeTime = 0;

	switch (geoType)
	{
	case PxGeometryType::Enum::eSPHERE:
		shape = CreateShape(PxSphereGeometry(size));
		break;
	case PxGeometryType::Enum::ePLANE:
		shape = CreateShape(PxPlaneGeometry());
		break;
	case PxGeometryType::Enum::eCAPSULE:
		shape = CreateShape(PxCapsuleGeometry(size, size));
		break;
	case PxGeometryType::Enum::eBOX:
		shape = CreateShape(PxBoxGeometry(size, size, size));
		break;
	default:
		break;
	}

	renderItem = new RenderItem(shape, trnasform, color);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
	delete trnasform;
}

void Particle::integrate(double t)
{
	// Euler Semi-Implicito

	velo = velo * std::pow(damping, t); // Damping

	velo = velo + acele * t; // Aceleraci�n

	trnasform->p += PxVec3(velo.x, velo.y, velo.z) * t; // Seteamos posicion	
}

void Particle::decreaseLife(double t)
{
	lifeTime += t;
}