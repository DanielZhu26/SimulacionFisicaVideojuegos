#include "ParticleSystem.h"
#include "NormalPartGen.h"
#include "UniPartGen.h"
#include "RainGen.h"
#include "SmokeGen.h"
#include "SparkGen.h"
#include "RigidSolidGen.h"

ParticleSystem::ParticleSystem()
{
	gravityGen = new GravityForceGenerator(Vector3D<>(0, -9.8, 0));
	windGen = new WindForceGen(Vector3D<>(1, 0, 0), 35, 0.5, Vector3D<>(0, 0, 0), 1000);
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
	p->AddForceGen(windGen);
	//p->AddForceGen(torbellinoGen);
	//p->AddForceGen(explosionGen);

	partList.push_back(p);
}

void ParticleSystem::addSolidRigid(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material, Vector3D<> pos,
	float density, Vector3D<> dimentions, float lifeTime, PxVec4 color)
{
	SolidRigid* solid = new SolidRigid(gPhysics, gScene, material, pos, dimentions, density, lifeTime, color);

	solidList.push_back(solid);
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

int ParticleSystem::addRigidSolidGen(PxPhysics* gPhysics, PxScene* gScene, PxMaterial* material, Vector3D<> pos, Vector3D<> dir, float density, 
	Vector3D<> dim, int cantidad, float lifeTime, PxVec4 color, float genTime) {
	RigidSolidGen* rigidGen = new RigidSolidGen(gPhysics, gScene, material, pos, dir, density, dim, cantidad, lifeTime, color, this, genTime);
	rigidGen->setIndice(genList.size());
	rigidGenList.push_back(rigidGen);
	return rigidGen->getIndice();
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
	UpdateSolids(t);
	SolidRigidGen(t);
}

void ParticleSystem::GenerateParticleSpring()
{
	Particle* part1 = new Particle(Vector3D<>(0, 20, 0), Vector3D<>(0, 0, 0), 1, physx::PxGeometryType::Enum::eSPHERE, 1, physx::PxVec4(0.5, 1.0, 0.5, 1.0));
	Particle* part2 = new Particle(Vector3D<>(0, 0, 0), Vector3D<>(0, 0, 0), 2, physx::PxGeometryType::Enum::eSPHERE, 1, physx::PxVec4(1.0, 0.5, 1.0, 1.0));

	SpringForceGenerator* fg1 = new SpringForceGenerator(1, 10, part2);
	SpringForceGenerator* fg2 = new SpringForceGenerator(0.5, 10, part1);

	part1->AddForceGen(fg1);
	part2->AddForceGen(fg2);

	partList.push_back(part1);
	partList.push_back(part2);
	forceGenList.push_back(fg1);
	forceGenList.push_back(fg2);
}

void ParticleSystem::GenerateAnchoredSpring()
{
	Particle* part3 = new Particle(Vector3D<>(0, 20, 0), Vector3D<>(0, 0, 0), 1, physx::PxGeometryType::Enum::eSPHERE, 1, physx::PxVec4(0.5, 1.0, 0.5, 1.0));
	AnchoredSpringFG* f3 = new AnchoredSpringFG(2, 10, Vector3D<>(0, 40, 0));
	part3->AddForceGen(f3);
	partList.push_back(part3);
	forceGenList.push_back(f3);
}

void ParticleSystem::GenerateBuoyancy()
{
	Particle* floatingObject = new Particle(Vector3D<>(0, 22, 0), Vector3D<>(0, 0, 0), 5, physx::PxGeometryType::Enum::eBOX, 2, physx::PxVec4(0.0, 1.0, 1.0, 1.0));
	//Particle* partiallySubmerged = new Particle(Vector3D<>(0, 22, 0), Vector3D<>(0, 0, 0), 20, physx::PxGeometryType::Enum::eBOX, 2, physx::PxVec4(1.0, 0.0, 0.0, 1.0));
	//Particle* sinkingObject = new Particle(Vector3D<>(0, 22, 0), Vector3D<>(0, 0, 0), 40, physx::PxGeometryType::Enum::eBOX, 2, physx::PxVec4(0.5, 0.5, 1.0, 1.0));
	Particle* plano = new Particle(Vector3D<>(0, 0, 0), 20, 20, -100);

	//Cuando mas aumente la densidad mas flotara
	BuoyancyForceGenerator* fg2 = new BuoyancyForceGenerator(2, 1, 1, plano); // Agua (el objeto flotará si su densidad es <= 1)

	Particle* part = floatingObject;

	part->AddForceGen(fg2);
	part->AddForceGen(gravityGen);

	partList.push_back(part);
	partList.push_back(plano);
	forceGenList.push_back(fg2);
}



void ParticleSystem::ParticlesGen()
{
	for (Fuente* gen : genList) {
		gen->ParticleGen();
	}
}


void ParticleSystem::SolidRigidGen(double t)
{
	for (RigidSolidGen* gen : rigidGenList)
	{
		gen->SolidGen(t);
	}
}

void ParticleSystem::DeleteSolidRigids(double t)
{
	for (RigidSolidGen* gen : rigidGenList)
	{
		
	}

}

void ParticleSystem::UpdateSolids(double t)
{
	for (SolidRigid* p : solidList) {
		p->update(t);
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

