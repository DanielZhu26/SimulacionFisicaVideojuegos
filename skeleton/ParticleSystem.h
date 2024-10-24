#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "Fuente.h"
#include "UniPartGen.h"
#include "NormalPartGen.h"

enum generators_type {

	NORMAL,
	UNIFORM
	
};

class ParticleSystem
{
private:
	std::list<Particle*> partList;
	std::vector<Fuente*> genList; 
	std::vector<Particle*> deleteVector;

	Vector3 mid = Vector3(0, 0, 0);

	//Radio max donde se encuentran las particulas
	float radioMax;
	double partLifeTime = 5.0;

public:
	ParticleSystem() {}

	~ParticleSystem();


	void update(double t);

	void deleteParticle(Particle* p);

	void addParticle(Particle* p);

	void addUniPartGen(Vector3 pos, Vector3 direction, float rate, float range, float spawnR, spawnDist sd);
	void addNormalPartGen(Vector3 pos, Vector3 direction, float rate, Vector3 dev, float spawnR, spawnDist sd);

	void setCenter(Vector3 c) { mid = c; }
	Vector3 getCenter() const { return mid; }

	void changeParticleLifeTime(float t) { partLifeTime = t; }
	float getParticleLifeTime() const { return partLifeTime; }

	void setRatius(float r) { radioMax = r; }
	float getRatius() const { return radioMax; }
	
};
