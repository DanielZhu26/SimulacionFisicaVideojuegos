#include "Particle.h"
#include <math.h>
#include <iostream>
#include "ParticleSystem.h"


Particle::Particle(PxVec3 pos, PxVec3 vel, PxVec3 acel, double masa, double lifeT) : pose(pos), velo(vel), acele(acel), mass(masa), lifeTime(lifeT)
{

	Init(pos, vel, acel);
	livedTime = 0.0;
	damping = 0.99;
}

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acel) {
	Init(pos, vel, acel);
	livedTime = 0.0;
	damping = 0.99;
}

void Particle::Init(Vector3 pos, Vector3 vel, Vector3 acel) {
	velo = vel;
	acele = acel;
	transform = physx::PxTransform(pos);
	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, &transform,Vector4(0,455,0,1));
	
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	renderItem = nullptr;
}

void Particle::Integrate(double t)
{


	// Actualizamos la velocidad con la aceleración
	velo = velo + acele * t;

	// Actualizamos la posición con la velocidad
	pose = pose + velo * t;

	// Actualizamos la posición del transform
	transform.p = pose;

	// Aplicamos el damping para amortiguar la velocidad
	velo = velo * pow(damping, t);


	
}

void Particle::update(double t,ParticleSystem& sys)
{
	livedTime += t;
	Integrate(t);
	if (livedTime > lifeTime || !isInside(sys.getCenter(), sys.getRatius())) sys.deleteParticle(this);
}

bool Particle::isInside(Vector3 const& v, float radio)
{
	return (transform.p - v).magnitude() < radio;
}

void Particle::SetAccel(PxVec3 newAcel) 
{	
	acele = newAcel;
}

void Particle::SetVel(PxVec3 newVel) {
	velo = newVel;
}

