#include "SolidRigid.h"

// Constructor
SolidRigid::SolidRigid(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material,
    Vector3D<> pos, Vector3D<> dimensions,float density, float lifetime, PxVec4 color, PxVec3 f)
    : lifetime(lifetime), position(pos), col(color), force(f)
{

   

   
    transform = new PxTransform(PxVec3(position.x, position.y, position.z));
    // Crear el actor dinamico
    rigidDynamic = gPhysics->createRigidDynamic(*transform);

    // Crear la forma del sólido 
    PxShape* shape = CreateShape(PxBoxGeometry(dimensions.x, dimensions.y, dimensions.z));
    rigidDynamic->attachShape(*shape);


    PxRigidBodyExt::updateMassAndInertia(*rigidDynamic, 0.15);
    rigidDynamic->setMass(density * dimensions.x * dimensions.y * dimensions.z);
    


    gScene->addActor(*rigidDynamic);

    renderItem = new RenderItem(shape, rigidDynamic, col);
    //RegisterRenderItem(renderItem);

}

SolidRigid::~SolidRigid()
{
    DeregisterRenderItem(renderItem);
    delete renderItem;
 
}


void SolidRigid::update(float deltaTime) {

    updateForce(deltaTime);

 /*   if (lifetime > 0) {
        lifetime -= deltaTime;
        if (lifetime <= 0) {
            delete this;
        }
    }*/
}

void SolidRigid::AddForceGen(ForceGen* forceGen)
{
    forceGens.push_back(forceGen);
}

void SolidRigid::updateForce(double t)
{
    //wind 1, gravity 2, explosion 3, tornado 4, flotacion 5
    for (auto forceGen : forceGens) {
        if (forceGen->getType() == 1)
        {
            //force = PxVec3(8, 0, 0);
            rigidDynamic->addForce(force, PxForceMode::eIMPULSE);
        }
        else if (forceGen->getType() == 2)
        {
            force = PxVec3(0, -2, 0);
            rigidDynamic->addForce(force, PxForceMode::eIMPULSE);
        }
        else 
        {
            /*force = PxVec3(position.x, position.y, position.z);
            rigidDynamic->addForce(force, PxForceMode::eIMPULSE);*/
        }
    

    }

}
void SolidRigid::decreaseLife(double t)
{
    lifetime += t;

}

