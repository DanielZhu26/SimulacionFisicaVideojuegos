#pragma once

#include <list>
#include "Vector3D.h"
#include <PxPhysicsAPI.h>
#include "ForceGen.h"


using namespace std;
using namespace physx;
class Fuente;
class Particle;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();


	void addParticle(Vector3D<> pos, Vector3D<> vel, const PxGeometryType::Enum& geoType = PxGeometryType::Enum::eSPHERE,
		float size = 1, const PxVec4& color = PxVec4(1.0, 1.0, 0.0, 1.0));

	int addUniPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel);
	int addNormalPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel);
	int addLluvia(Vector3D<> pos, float rad, int force);
	int addSmoke(Vector3D<> pos, int force);
	int addSpark(Vector3D<> pos, int force);

	void addForceGen(ForceGen* fg);


	void Update(double t);

private:

	void ParticlesGen();
	void DeleteParticles();
	void UpdateParticles(double t);

	list<Fuente*> genList;
	list<Particle*> partList;
	list<ForceGen*> forceGensList;

	float max_lifeTime = 5;
	float max_distance = 100;

	
};
