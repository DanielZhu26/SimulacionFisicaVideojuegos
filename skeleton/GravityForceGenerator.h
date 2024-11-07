#pragma once
#include "ForceGen.h"

class GravityForceGenerator : public ForceGen {
public:
    GravityForceGenerator(const Vector3D<> gravity) : gravity(gravity) {}
    virtual void applyForce(Particle& particle) override;

private:
    Vector3D<> gravity;  
};
