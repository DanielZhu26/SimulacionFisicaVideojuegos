#ifndef SOLID_RIGID_H
#define SOLID_RIGID_H

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "ForceGen.h"

using namespace physx;
class ForceGen;

class SolidRigid {
private:
    PxRigidDynamic* rigidDynamic;
    RenderItem* renderItem;       
    float lifetime;      
    Vector3D<> position;
    PxVec3 force;
    PxVec4 col; //COlor
    std::vector<ForceGen*> forceGens;
    PxTransform* transform;
public:

    SolidRigid(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material,
        Vector3D<> pos, Vector3D<> dimensions,
        float density, float lifetime, PxVec4 color);

    ~SolidRigid();

    // Metodo para actualizar el tiempo de vida
    void update(float deltaTime);

    void AddForceGen(ForceGen* forceGen);
    void updateForce(double t);

    void ApplyForce(Vector3D<> force);

    float getLifeTime() { return lifetime; }
    Vector3D<> getPos() { return position; }
    void decreaseLife(double t);
};

#endif // SOLID_RIGID_H
