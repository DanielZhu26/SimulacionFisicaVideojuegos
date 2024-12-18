#pragma once

#include "Vector3D.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include <random>

class Fuente
{
public:
	Fuente(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel, ParticleSystem* sysR, float lifetime);
	~Fuente();

	void setIndice(int id) { this->id = id; };
	int getIndice() { return id; };

	virtual void ParticleGen() = 0;

	//void SetParticleModel(Particle* p) { partRef = p; };
	void Fuente::updateLifetime(float deltaTime) {
		life -= deltaTime;
	}

	bool Fuente::isExpired() const {
		return life <= 0.0f;
	}
protected:

	int id;
	Vector3D<> position;
	Vector3D<> direction;
	float vel;
	float deltAngle;
	float deltVel;

	Particle* partRef;
	ParticleSystem* systemRef;
	float life;
	std::mt19937 rnd;
};
