#include "RigidSolidGen.h"

RigidSolidGen::RigidSolidGen(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material, Vector3D<> pos, Vector3D<> dir,
    float density, Vector3D<> dimentions, int cantidad, float lifeTime, PxVec4 color, ParticleSystem* sysS, float genTime, PxVec3 f)
    : density(density), size(size), physics(gPhysics), scene(gScene), mat(material), position(pos), direction(dir), dim(dimentions), 
    num(cantidad), lftime(lifeTime), col(color), sys(sysS), generationInterval(genTime), force(f){}

RigidSolidGen::~RigidSolidGen() {
  
}

void RigidSolidGen::SolidGen(float deltaTime) {
    timeSinceLastGen += deltaTime;

    // Verificar si ha pasado el intervalo para generar un nuevo sólido
    if (timeSinceLastGen > generationInterval && num > 0) {
        // Generar un nuevo sólido

        sys->addSolidRigid(physics, scene, mat, position, density, dim, lftime, col, force);

        // Reiniciar temporizador y reducir el número de sólidos restantes
        timeSinceLastGen = 0;
        num--;
    }
}



