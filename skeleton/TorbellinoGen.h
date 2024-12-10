#pragma once

#include "WindForceGen.h"


class TorbellinoGen : public WindForceGen
{
public:
	TorbellinoGen(float force, float friction, Vector3D<> pos, float range);
	TorbellinoGen();

	void updateF(Particle* p, double t) override;

	bool onRange(Vector3D<> pos) const;

};

