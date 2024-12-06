#include "SolidRigid.h"

// Constructor
SolidRigid::SolidRigid(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material,
    Vector3D<> pos, Vector3D<> dimensions,float density, float lifetime, PxVec4 color)
    : lifetime(lifetime), position(pos), col(color)
{
    // Crear la forma del sólido 
    PxShape* shape = gPhysics->createShape(PxBoxGeometry(dimensions.x, dimensions.y, dimensions.z), *material);

    // Crear el actor dinamico
    rigidDynamic = gPhysics->createRigidDynamic(PxTransform(PxVec3(position.x, position.y, position.z)));
    rigidDynamic->attachShape(*shape);

    // Calcular la masa y los momentos de inercia manualmente
    PxVec3 inertiaTensor(
        (1.0f / 12.0f) * density * (dimensions.y * dimensions.y + dimensions.z * dimensions.z), // Ixx
        (1.0f / 12.0f) * density * (dimensions.x * dimensions.x + dimensions.z * dimensions.z), // Iyy
        (1.0f / 12.0f) * density * (dimensions.x * dimensions.x + dimensions.y * dimensions.y)  // Izz
    );
    rigidDynamic->setMass(density * dimensions.x * dimensions.y * dimensions.z);
    rigidDynamic->setMassSpaceInertiaTensor(inertiaTensor);


    gScene->addActor(*rigidDynamic);

    renderItem = new RenderItem(shape, rigidDynamic, col);

}

SolidRigid::~SolidRigid()
{
    DeregisterRenderItem(renderItem);
    delete renderItem;
 
}


void SolidRigid::update(float deltaTime) {
    if (lifetime > 0) {
        lifetime -= deltaTime;
        if (lifetime <= 0) {
            delete this;
        }
    }
}
