#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "Fuente.h"
#include "UniformGenerator.h"
//#include "NormalGenerator.h"

enum generators_type {
	UNIFORM,
	NORMAL
};

class ParticleSystem
{
private:
	std::list<Particle* > pList;
	std::vector<Fuente* > gList; 
	std::vector<Particle*> deleteVector;

	Vector3 mid = Vector3(0, 0, 0);

	//Radio max donde se encuentran las particulas
	float radioMax;
	double partLifeTime = 5.0;

public:
	ParticleSystem() {}

	~ParticleSystem() {
		for (auto p : pList) {
			delete p;
			p = nullptr;
		}
		for (auto g : gList) {
			delete g;
			g = nullptr;
		}

		pList.clear();
		gList.clear();

	}


	void update(double t);

	void killParticle(Particle* p);

	void addParticle(Particle* p);

	void addGenerator(Vector3 pos, float rate, generators_type type);

	void setCenter(Vector3 c) { mid = c; }
	Vector3 getCenter() const { return mid; }

	void changeParticleLifeTime(float t) { partLifeTime = t; }
	float getParticleLifeTime() const { return partLifeTime; }

	void setRatius(float r) { radioMax = r; }
	float getRatius() const { return radioMax; }
	
};
