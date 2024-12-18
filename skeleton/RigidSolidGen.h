#ifndef RIGID_SOLID_GEN_H
#define RIGID_SOLID_GEN_H

#include <vector>
#include "SolidRigid.h"
#include <PxPhysicsAPI.h>
#include "ParticleSystem.h"

class RigidSolidGen 
{
protected:


    float density;                     // Densidad para los sólidos rígidos
    float size;                        // Tamaño del sólido
    PxPhysics* physics;
    PxScene* scene;
    PxMaterial* mat;
    Vector3D<> position;
    Vector3D<> direction;
    Vector3D<> dim;
    int num; //Numero de solidos a generar
    float lftime;
    PxVec4 col; //Color
    int id;
    ParticleSystem* sys;
    PxVec3 force;

    float generationInterval;   // Tiempo entre generaciones
    float timeSinceLastGen = 0;     // Tiempo acumulado desde la última generación
   

public:
    RigidSolidGen(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material, Vector3D<> pos, Vector3D<> dir, float density,
        Vector3D<> dimentions, int cantidad, float lifeTime, PxVec4 color, ParticleSystem* sysS, float genTime, PxVec3 f);
    ~RigidSolidGen();

    void setIndice(int id) { this->id = id; };
    int getIndice() { return id; };
   

    void SolidGen(float deltaTime); // Sobrescribir para generar sólidos
    //void clearSolids(float deltaTime);   // Limpiar sólidos generados

 
  
};

#endif // RIGID_SOLID_GEN_H
