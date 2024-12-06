#include "RigidSolidGen.h"

RigidSolidGen::RigidSolidGen(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material, Vector3D<> pos, Vector3D<> dir,
    float density, Vector3D<> dimentions, int cantidad, float lifeTime, PxVec4 color, ParticleSystem* sysS, float genTime)
    : density(density), size(size), physics(gPhysics), scene(gScene), mat(material), position(pos), direction(dir), dim(dimentions), 
    num(cantidad), lftime(lifeTime), col(color), sys(sysS), generationInterval(genTime){}

RigidSolidGen::~RigidSolidGen() {
  
}

void RigidSolidGen::SolidGen(float deltaTime) {
    cout << deltaTime << endl;
    // Verificar si ha pasado el intervalo para generar un nuevo s�lido
    if (deltaTime - timeSinceLastGen >= generationInterval && num > 0) {
        // Generar un nuevo s�lido
        Vector3D<> spawnPosition = position;
         spawnPosition = spawnPosition + direction * (1.0f - float(num) / 10.0f); // Variar ligeramente posici�n

        sys->addSolidRigid(physics, scene, mat, position, density, dim, lftime, col);

        // Reiniciar temporizador y reducir el n�mero de s�lidos restantes
        timeSinceLastGen = deltaTime;
        num--;
    }
}



