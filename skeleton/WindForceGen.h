#pragma once

#include "ForceGen.h"
#include "Vector3D.h"

class WindForceGen : public ForceGen
{
public:
    WindForceGen(Vector3D<> dir, float force, float friction, Vector3D<> pos, float range);
    WindForceGen(float force, float friction, Vector3D<> pos, float range);
    ~WindForceGen();

    void updateF(Particle* p, double t) override;

    bool onRange(Vector3D<> pos) const;

protected:

    float windF;
    float friction;
    float range;

    Vector3D<> windVel;
    Vector3D<> position;

   

};

