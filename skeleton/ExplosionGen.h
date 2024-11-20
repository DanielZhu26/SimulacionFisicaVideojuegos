#pragma once

#include "ForceGen.h"
#include "RenderUtils.hpp"

class ExplosionGen : public ForceGen
{
public:
	ExplosionGen(float force, float range, Vector3D<> pos);
	~ExplosionGen();

	void updateF(Particle* p, double t) override;

	void updateGen(double t);

	void addOnda(float vel);

	
private:

	float exploForce;
	float exploRange;
	Vector3D<> position;
	float euler = 2.71828;

	struct Onda {
		float range;
		float vel;
		float duration;

		// Constructor
		Onda(float r, float v, float t) : range(r), vel(v), duration(t) {}
	};

	std::list<Onda> ondasList;


};

