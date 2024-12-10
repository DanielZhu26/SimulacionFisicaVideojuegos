#pragma once

#include <list>
#include "Vector3D.h"
#include <PxPhysicsAPI.h>

#include "GravityForceGenerator.h"
#include "WindForceGen.h"
#include "TorbellinoGen.h"
#include "ExplosionGen.h"

#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "BuoyancyForceGenerator.h"
#include "SolidRigid.h"


using namespace std;
using namespace physx;
class Fuente;
class Particle;
class RigidSolidGen;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();


	void addParticle(Vector3D<> pos, Vector3D<> vel, float mass, const PxGeometryType::Enum& geoType = PxGeometryType::Enum::eSPHERE,
		float size = 1, const PxVec4& color = PxVec4(1.0, 1.0, 0.0, 1.0));

	void addSolidRigid(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material, Vector3D<> pos,
		float density, Vector3D<> dimentions, float lifeTime, PxVec4 color);

	int addUniPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel);
	int addNormalPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel);
	int addLluvia(Vector3D<> pos, float rad, int force);
	int addSmoke(Vector3D<> pos, int force);
	int addSpark(Vector3D<> pos, int force);

	int addRigidSolidGen(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material, Vector3D<> pos, Vector3D<> dir, float density,
		Vector3D<> dim, int cantidad, float lifeTime, PxVec4 color, float genTime);


	void Explosion();
	void Update(double t);

	void GenerateParticleSpring();
	void GenerateAnchoredSpring();
	void GenerateBuoyancy();

private:

	void ParticlesGen();
	void DeleteParticles();
	void UpdateParticles(double t);
	void SolidRigidGen(double t);
	void DeleteSolidRigids();
	void UpdateSolids(double t);

	list<Fuente*> genList;
	list<Particle*> partList;
	list<ForceGen*> forceGenList;
	list<RigidSolidGen*> rigidGenList;
	list<SolidRigid*> solidList; // Lista de sólidos generados

	float max_lifeTime = 115;
	float max_distance = 2000;
	float solidmaxlife = 10;
	float maxsoliddistance = 30;

	GravityForceGenerator* gravityGen;
	WindForceGen* windGen;
	TorbellinoGen* torbellinoGen;
	ExplosionGen* explosionGen;

	PxPhysics* physics;
	PxScene* scene;
	PxMaterial* mat;


	
};
