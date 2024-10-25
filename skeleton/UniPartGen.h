#pragma once

#include "Fuente.h"


class UniPartGen : public Fuente
{
public:
	UniPartGen(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef);
	~UniPartGen();

private:

	void GenerateParticle() override;
	Vector3D<> RandomDir();
	float RandomSpeed();


	std::uniform_real_distribution<> uniformDist;
};
