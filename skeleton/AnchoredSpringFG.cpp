#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3D<>& anchor_pos) :
	SpringForceGenerator(k, resting, nullptr)
{
	_other = new Particle(anchor_pos, Vector3D<>(0, 0, 0), 1, physx::PxGeometryType::Enum::eBOX, 2, physx::PxVec4(0.25f, 0.12f, 0.03f, 1.0f));
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete _other;
}