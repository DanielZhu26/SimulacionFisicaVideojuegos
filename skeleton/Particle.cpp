#include "Particle.h"

#include "RenderUtils.hpp"
#include "ForceGen.h"
#include <cmath>

using namespace physx;

Particle::Particle(PxVec3 pos, PxVec3 vel, PxVec3 acel):posit(pos), speed(vel), accel(acel)
{
	transform = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	PxSphereGeometry geo(1);
	PxShape* shape = CreateShape(geo);

	renderItem = new RenderItem(shape, transform, Vector4(1, 0.5, 1, 1));
	RegisterRenderItem(renderItem);
	damping = 0.99;
}


Particle::Particle(Vector3D<> pos, Vector3D<> vel, float masa, const PxGeometryType::Enum& geoType, float size, const PxVec4& color)
{
	transform = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	velo = vel;
	PxShape* shape = nullptr;
	lifeTime = 0;

	mass = masa;

	if(geoType == PxGeometryType::Enum::eSPHERE)
		shape = CreateShape(PxSphereGeometry(size));
	else if(geoType == PxGeometryType::Enum::eBOX)
		shape = CreateShape(PxBoxGeometry(size, size, size));


	//shape = CreateShape(PxSphereGeometry(size));


	renderItem = new RenderItem(shape, transform, color);
}

Particle::Particle(Vector3D<> pos, float ladoX, float ladoZ, float masa, const physx::PxVec4& color)
{
	transform = new PxTransform(PxVec3(pos.x, pos.y, pos.z));

	velo = Vector3D<>();
	acele = Vector3D<>();
	mass = masa;
	damping = 0;
	lifeTime = -1000;

	renderItem = new RenderItem(CreateShape(PxBoxGeometry(ladoX, 1, ladoZ)), transform, color);
}


Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
	delete transform;
}

void Particle::semiIntegrate(double t)
{
	// Semi-Implicito
	velo = velo * std::pow(damping, t);

	velo = velo + acele * t; 

	transform->p += PxVec3(velo.x, velo.y, velo.z) * t; 

	
}

void Particle::Integrate(double t)
{
	// Actualizamos la velocidad
	speed = speed * pow(damping, t) + accel * t;

	// ACtualizamos la aceleracion
	posit = posit + speed * t;

	// Actualizamos la posici�n del transform
	transform->p = transform->p + speed * t;
}

void Particle::decreaseLife(double t)
{
	lifeTime += t;
}

void Particle::AddForceGen(ForceGen* forceGen)
{
	forceGens.push_back(forceGen);
}

void Particle::updateForce(double t)
{
	for (auto forceGen : forceGens) {
		forceGen->updateF(this, t);
	}

}

void Particle::ApplyForce(Vector3D<> force)
{
	velo = velo + force / mass;
}

void Particle::ApplyForceCont(Vector3D<> force)
{
	acele = acele + force / mass;
}
