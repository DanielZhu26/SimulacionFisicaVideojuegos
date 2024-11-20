#include "WindForceGen.h"



WindForceGen::WindForceGen(Vector3D<> dir, float force, float friction, Vector3D<> pos, float range):
	ForceGen(), windVel(dir.GetNormalized() * force), windF(force), friction(friction), position(pos), range(range)
{

}

WindForceGen::WindForceGen(float force, float friction, Vector3D<> pos, float range):
	ForceGen(), windVel(Vector3D<>(0, 0, 0)), windF(force), friction(friction), position(pos), range(range)
{

}

WindForceGen::~WindForceGen()
{

}

void WindForceGen::updateF(Particle* p, double t)
{
	Vector3D<> partPOs = p->getPos();

	if (onRange(partPOs)) 
	{
		Vector3D<> f = (windVel - p->getVel()) * friction;
		p->ApplyForce(f * t);
	}
}

bool WindForceGen::onRange(Vector3D<> pos) const
{
	return (abs(pos.x - position.x) < range / 2) && (abs(pos.y - position.y) < range / 2)
		&& (abs(pos.z - position.z) < range / 2);
}