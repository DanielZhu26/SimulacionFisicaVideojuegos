//#include "RigidSolidGen.h"
//
//RigidSolidGen::RigidSolidGen(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material, Vector3D<> pos, Vector3D<> dir, float density, Vector3D<> dimentions, ParticleSystem* sysR, int cantidad)
//    : Fuente(pos, dir, 0, 0, 0, sysR), density(density), size(size), physics(gPhysics), scene(gScene), mat(material), position(pos), dim(dimentions), num(cantidad){}
//
//RigidSolidGen::~RigidSolidGen() {
//    clearSolids();
//}
//
//void RigidSolidGen::ParticleGen() {
//    // Generar un sólido rígido en una posición específica
//    SolidRigid* solid = new SolidRigid(physics, scene, mat, position, dim, density);
//
//    solidList.push_back(solid);
//}
//
//void RigidSolidGen::clearSolids() {
//    for (SolidRigid* solid : solidList) {
//        delete solid; 
//    }
//    solidList.clear();
//}
