#include "ParticleSystem.h"
#include "NormalPartGen.h"
#include "UniPartGen.h"
//#include "RainGenerator.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}


int ParticleSystem::AddUniformGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta)
{
	Fuente* generator = new UniPartGen(position, direction, speed, angleDelta, speedDelta, this);
	generator->SetID(generators.size());
	generators.push_back(generator);
	return generator->GetID();
}

int ParticleSystem::AddGaussianGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta)
{
	Fuente* generator = new NormalPartGen(position, direction, speed, angleDelta, speedDelta, this);
	generator->SetID(generators.size());
	generators.push_back(generator);
	return generator->GetID();
}
//
//int ParticleSystem::AddRainGenerator(Vector3D<> position, float radius, int intensity)
//{
//	ParticleGenerator* generator = new RainGenerator(position, radius, intensity, this);
//	generator->SetID(generators.size());
//	generators.push_back(generator);
//	return generator->GetID();
//}

void ParticleSystem::AddParticle(Vector3D<> position, Vector3D<> velocity, const physx::PxGeometryType::Enum& geoType, float size, const physx::PxVec4& color)
{
	Particle* p = new Particle(position, velocity, geoType, size, color);
	p->SetAceleration(Vector3D<>(0, -9.8, 0));
	particles.push_back(p);
}


void ParticleSystem::Update(double t)
{
	GenerateParticles();
	KillParticles();
	UpdateParticles(t);
}

void ParticleSystem::GenerateParticles()
{
	for (Fuente* gen : generators) {
		gen->GenerateParticle();
	}
}

void ParticleSystem::KillParticles()
{
	for (auto it = particles.begin(); it != particles.end(); ) {
		if ((*it)->GetPosition().GetMagnitude() > MAX_DISTANCE || (*it)->GetLifeTime() > MAX_LIFETIME) {
			delete* it;
			it = particles.erase(it); // borra y avanza el iterador
		}
		else {
			++it; // solo avanza el iterador si no se borr� el elemento
		}
	}
}

void ParticleSystem::UpdateParticles(double t)
{
	for (Particle* p : particles) {
		p->Integrate(t);
		p->UpdateState(t);
	}
}