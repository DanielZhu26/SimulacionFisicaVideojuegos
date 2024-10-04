#include "Particle.h"


Particle::Particle(PxVec3 pos, PxVec3 vel, PxVec3 acel) : pose(pos), velo(vel), acele(acel)
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
	// Actualizamos la velocidad
	velo = velo * pow(damping, t) + acele * t;

	// ACtualizamos la aceleracion
	pose = pose + velo * t;

	// Actualizamos la posición del transform
	transform->p = transform->p + velo * t;
}

