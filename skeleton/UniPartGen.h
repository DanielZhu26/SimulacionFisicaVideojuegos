#pragma once

#include "Fuente.h"


class UniPartGen : public Fuente
{
public:
	UniPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel, ParticleSystem* sysR);
	~UniPartGen();

private:

	void ParticleGen() override;
	Vector3D<> CalculateRndDir();
	float CalcRndVel();


	std::uniform_real_distribution<> dist_uniforme;
};
