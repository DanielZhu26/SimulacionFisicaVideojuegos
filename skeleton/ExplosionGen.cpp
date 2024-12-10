#include "ExplosionGen.h"

ExplosionGen::ExplosionGen(float force, float range, Vector3D<> pos) :
	ForceGen(), exploForce(force), exploRange(range), position(pos)
{
	type = 3;
}

ExplosionGen::~ExplosionGen()
{
}

void ExplosionGen::updateF(Particle* p, double t)
{
	Vector3D<> dir = p->getPos() - position;
	float distance = dir.getMagnitude();
	for (Onda sw : ondasList) {
		if (distance < sw.range) {
			p->ApplyForce(dir * (exploForce / pow(distance, 2)) * pow(euler, -sw.duration / 0.1));
		}
	}

	
}

void ExplosionGen::updateGen(double t)
{

	// Actualizar la duración y el rango de la onda
	for (auto it = ondasList.begin(); it != ondasList.end(); ) {
		it->duration += t;
		it->range = it->vel * it->duration;

		// Eliminar la onda si supera el rango de la explosión
		if (it->range > exploRange)
			it = ondasList.erase(it);
		else
			++it;
	}
}

void ExplosionGen::addOnda(float vel)
{
	
	ondasList.emplace_back(0, vel, 0);
}
