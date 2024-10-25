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

void ParticleSystem::addParticle(Vector3D<> pos, Vector3D<> vel, const PxGeometryType::Enum& geoType, float size, const PxVec4& color)
{
	Particle* p = new Particle(pos, vel, geoType, size, color);
	p->setAccel(Vector3D<>(0, -9.8, 0));
	partList.push_back(p);
}


int ParticleSystem::addUniPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel)
{
	Fuente* unifGen = new UniPartGen(pos, dir, vel, deltAngle, deltVel, this);
	unifGen->setIndice(genList.size());
	genList.push_back(unifGen);
	return unifGen->getIndice();
}

int ParticleSystem::addNormalPartGen(Vector3D<> pos, Vector3D<> dir, float vel, float deltAngle, float deltVel)
{
	Fuente* generator = new NormalPartGen(pos, dir, vel, deltAngle, deltVel, this);
	generator->setIndice(genList.size());
	genList.push_back(generator);
	return generator->getIndice();
}
//
//int ParticleSystem::AddRainGenerator(Vector3D<> position, float radius, int intensity)
//{
//	ParticleGenerator* generator = new RainGenerator(position, radius, intensity, this);
//	generator->SetID(generators.size());
//	generators.push_back(generator);
//	return generator->GetID();
//}


void ParticleSystem::Update(double t)
{
	ParticlesGen();
	DeleteParticles();
	UpdateParticles(t);
}

void ParticleSystem::ParticlesGen()
{
	for (Fuente* gen : genList) {
		gen->ParticleGen();
	}
}

void ParticleSystem::DeleteParticles()
{
	for (auto it = partList.begin(); it != partList.end(); ) {
		if ((*it)->getPos().getMagnitude() > max_distance || (*it)->getLifeTime() > max_lifeTime) {
			delete* it;
			it = partList.erase(it); 
		}
		else  
			++it; 
	}
}

void ParticleSystem::UpdateParticles(double t)
{
	for (Particle* p : partList) {
		p->integrate(t);
		p->decreaseLife(t);
	}
}