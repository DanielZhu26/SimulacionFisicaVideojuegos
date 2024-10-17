#include "Particle.h"


Particle::Particle(PxVec3 pos, PxVec3 vel, PxVec3 acel, double masa, double lifeT) : pose(pos), velo(vel), acele(acel), mass(masa), lifeTime(lifeT)
{
	transform = new PxTransform(pose);
	PxSphereGeometry geo(1);
	PxShape* shape = CreateShape(geo);

	renderItem = new RenderItem(shape, transform, Vector4(1, 0.5, 1, 1));
	RegisterRenderItem(renderItem);
	damping = 0.99;
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
	delete transform;
}

void Particle::Integrate(double t)
{
	if (lifeTime <= 0) return;  

	// Actualizamos la velocidad con la aceleración
	velo = velo + acele * t;

	// Actualizamos la posición con la velocidad
	pose = pose + velo * t;

	// Actualizamos la posición del transform
	transform->p = pose;

	// Aplicamos el damping para amortiguar la velocidad
	velo = velo * pow(damping, t);

	lifeTime -= t;
}

void Particle::SetAccel(PxVec3 newAcel) 
{	
	acele = newAcel;
}

void Particle::SetVel(PxVec3 newVel) {
	velo = newVel;
}

