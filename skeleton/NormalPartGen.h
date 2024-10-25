#pragma once
#include "Fuente.h"
class NormalPartGen : public Fuente
{
public:
	NormalPartGen(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef);
	~NormalPartGen();

private:
	void GenerateParticle() override;
	Vector3D<> RandomDir();
	float RandomSpeed();


	std::normal_distribution<> gaussianDistAngle;
	std::normal_distribution<> gaussianDistSpeed;
};
