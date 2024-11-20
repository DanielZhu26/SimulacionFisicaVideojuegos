#pragma once

#include <list>
#include "Vector3D.h"
#include <PxPhysicsAPI.h>

#include "GravityForceGenerator.h"
#include "WindForceGen.h"
#include "TorbellinoGen.h"
#include "ExplosionGen.h"


using namespace std;
using namespace physx;
class Fuente;
class Particle;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();


	void addParticle(Vector3D<> pos, Vector3D<> vel, float mass, const PxGeometryType::Enum& geoType = PxGeometryType::Enum::eSPHERE,
		float size = 1, const PxVec4& color = PxVec4(1.0, 1.0, 0.0, 1.0));

	int addUniPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel);
	int addNormalPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel);
	int addLluvia(Vector3D<> pos, float rad, int force);
	int addSmoke(Vector3D<> pos, int force);
	int addSpark(Vector3D<> pos, int force);


	void Explosion();
	void Update(double t);

private:

	void ParticlesGen();
	void DeleteParticles();
	void UpdateParticles(double t);

	list<Fuente*> genList;
	list<Particle*> partList;

	float max_lifeTime = 115;
	float max_distance = 2000;

	GravityForceGenerator* gravityGen;
	WindForceGen* windGen;
	TorbellinoGen* torbellinoGen;
	ExplosionGen* explosionGen;

	
};
