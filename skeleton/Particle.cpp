#include "Particle.h"

#include "RenderUtils.hpp"
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
Particle::Particle(Vector3D<> pos, Vector3D<> vel, Vector3D<> acel, float mass)
	: pose(pos), velo(vel), acele(acel), mass(mass), lifeTime(0), damping(0.99) 
{
	transform = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	velo = vel;
	PxShape* shape = nullptr;
	lifeTime = 0;

	shape = CreateShape(PxSphereGeometry(0.5));


	renderItem = new RenderItem(shape, transform, Vector4(0, 0, 0, 1));

}

Particle::Particle(Vector3D<> pos, Vector3D<> vel, const PxGeometryType::Enum& geoType, float size, const PxVec4& color)
{
	transform = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	velo = vel;
	PxShape* shape = nullptr;
	lifeTime = 0;

	shape = CreateShape(PxSphereGeometry(size));


	renderItem = new RenderItem(shape, transform, color);
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