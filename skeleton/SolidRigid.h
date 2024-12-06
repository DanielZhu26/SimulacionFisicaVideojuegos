#ifndef SOLID_RIGID_H
#define SOLID_RIGID_H

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"

using namespace physx;

class SolidRigid {
private:
    PxRigidDynamic* rigidDynamic;
    RenderItem* renderItem;       
    float lifetime;      
    Vector3D<> position;
    PxVec4 col; //COlor
public:

    SolidRigid(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material,
        Vector3D<> pos, Vector3D<> dimensions,
        float density, float lifetime, PxVec4 color);

    ~SolidRigid();

    // Metodo para actualizar el tiempo de vida
    void update(float deltaTime);
};

#endif // SOLID_RIGID_H
