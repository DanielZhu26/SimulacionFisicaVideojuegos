//#ifndef RIGID_SOLID_GEN_H
//#define RIGID_SOLID_GEN_H
//
//#include <vector>
//#include "SolidRigid.h"
//#include "Fuente.h"
//#include <PxPhysicsAPI.h>
//
//class RigidSolidGen : public Fuente {
//private:
//    std::vector<SolidRigid*> solidList; // Lista de sólidos generados
//    float density;                     // Densidad para los sólidos rígidos
//    float size;                        // Tamaño del sólido
//    PxPhysics* physics;
//    PxScene* scene;
//    PxMaterial* mat;
//    Vector3D<> position;
//    Vector3D<> dim;
//    int num; //Numero de solidos a generar
//
//public:
//    RigidSolidGen(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material, Vector3D<> pos, Vector3D<> dir, float density, Vector3D<> dimentions, ParticleSystem* sysR, int cantidad);
//    ~RigidSolidGen();
//
//    void ParticleGen() override; // Sobrescribir para generar sólidos
//    void clearSolids();          // Limpiar sólidos generados
//};
//
//#endif // RIGID_SOLID_GEN_H
