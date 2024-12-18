#pragma once

#include "Fuente.h"

class RainGen : public Fuente
{
public:
	RainGen(Vector3D<> pos, float rad, int force, ParticleSystem* sysR, float lifetime);
	~RainGen();

private:
	void ParticleGen() override;

	Vector3D<> CalcRndPos();

	float rad;
	int force;
};