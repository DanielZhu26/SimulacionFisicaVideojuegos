#include "ParticleSystem.h"
#include "NormalPartGen.h"
#include "UniPartGen.h"
#include "RainGen.h"
#include "SmokeGen.h"
#include "SparkGen.h"

ParticleSystem::ParticleSystem()
{
	gravityGen = new GravityForceGenerator(Vector3D<>(0, -9.8, 0));
	windGen = new WindForceGen(Vector3D<>(1, 0, 0), 15, 0.5, Vector3D<>(0, 0, 0), 1000);
	torbellinoGen = new TorbellinoGen(1.0, 0.5, Vector3D<>(0, 0, 0), 1000);
	explosionGen = new ExplosionGen(500, 1000, Vector3D<>(0, 0, 10));
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::addParticle(Vector3D<> pos, Vector3D<> vel, float mass, const PxGeometryType::Enum& geoType, float size, const PxVec4& color)
{
	Particle* p = new Particle(pos, vel, mass, geoType, size, color);
	//p->setAccel(Vector3D<>(0, -9.8, 0));

	//Generadores de fuerzas
	p->AddForceGen(gravityGen);
	//p->AddForceGen(windGen);
	//p->AddForceGen(torbellinoGen);
	p->AddForceGen(explosionGen);

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
int ParticleSystem::addSmoke(Vector3D<> pos, int force)
{
	Fuente* smokeGen = new SmokeGen(pos, force, this);
	smokeGen->setIndice(genList.size());
	genList.push_back(smokeGen);
	return smokeGen->getIndice();
}

int ParticleSystem::addSpark(Vector3D<> pos, int force)
{
	Fuente* sparkGen = new SparkGen(pos, force, this);
	sparkGen->setIndice(genList.size());
	genList.push_back(sparkGen);
	return sparkGen->getIndice();
}



void ParticleSystem::Explosion()
{
	explosionGen->addOnda(1000);
}

void ParticleSystem::Update(double t)
{

	explosionGen->updateGen(t);

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
		p->updateForce(t);
	}
}