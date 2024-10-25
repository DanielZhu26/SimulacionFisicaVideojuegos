#pragma once

#include "Fuente.h"


class UniPartGen : public Fuente
{
public:
	UniPartGen(Vector3D<> pos, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* sysR);
	~UniPartGen();

private:

	void ParticleGen() override;
	Vector3D<> CalculateRndDir();
	float CalcRndVel();


	std::uniform_real_distribution<> dist_uniforme;
};
