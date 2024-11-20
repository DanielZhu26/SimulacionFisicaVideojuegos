#pragma once
#include "Fuente.h"
class NormalPartGen : public Fuente
{
public:
	NormalPartGen(Vector3D<> position, Vector3D<> direction, float vel, float angleDelta, float speedDelta, ParticleSystem* systemRef);
	~NormalPartGen();

private:
	void ParticleGen() override;
	Vector3D<> CalculateRndDir();
	float CalcRndVel();


	std::normal_distribution<> gaussianDistAngle;
	std::normal_distribution<> gaussianDistSpeed;
};
