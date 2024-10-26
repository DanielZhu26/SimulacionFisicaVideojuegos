#include "ParticleSystem.h"
#include "NormalPartGen.h"
#include "UniPartGen.h"
#include "RainGen.h"

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
int ParticleSystem::addLluvia(Vector3D<> pos, float rad, int force)
{
	Fuente* rainGen = new RainGen(pos, rad, force, this);
	rainGen->setIndice(genList.size());
	genList.push_back(rainGen);
	return rainGen->getIndice();
}



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
		p->semiIntegrate(t);
		p->decreaseLife(t);
	}
}