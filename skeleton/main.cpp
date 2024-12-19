#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Particle.h"
#include "Fuente.h"
#include "ParticleSystem.h"
#include "SolidRigid.h"



std::string display_text = "This is a test";

using namespace std;
using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;


//RenderItem* xRenderItem = NULL;
//RenderItem* yRenderItem = NULL;
//RenderItem* zRenderItem = NULL;
//RenderItem* aRenderItem = NULL;

//Particle* particle = nullptr;

vector<Particle*> particlesVector;

PxTransform* x, y, z, origin;

ParticleSystem* partSys = nullptr;
SolidRigid* solid = nullptr;
PxRigidDynamic* bulletActor = nullptr;
SolidRigid* bullet = nullptr;
list<SolidRigid*> balaList;

int score = 0;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);



	//Muelles
	//partSys->GenerateParticleSpring();
	//partSys->GenerateAnchoredSpring();
	//partSys->GenerateBuoyancy();

	//Create cabaña
		// Crear un obstáculo estático
	PxRigidStatic* obstacle = gPhysics->createRigidStatic(PxTransform(PxVec3(-120.0f, 15.5f, 0.0f)));
	PxShape* obstacleShape = gPhysics->createShape(PxBoxGeometry(5.0f, 100.0f, 250.0f), *gMaterial);
	obstacle->attachShape(*obstacleShape);
	RenderItem* obs1 = new RenderItem(obstacleShape, obstacle, PxVec4(Vector4(0.824, 0.412, 0.118, 1.0)));

	//// Crear un obstáculo estático
	PxRigidStatic* obstacle2 = gPhysics->createRigidStatic(PxTransform(PxVec3(120.0f, 15.5f, 0.0f)));
	PxShape* obstacleShape2 = gPhysics->createShape(PxBoxGeometry(5.0f, 110.0f, 250.0f), *gMaterial);
	obstacle->attachShape(*obstacleShape2);
	RenderItem* obs2 = new RenderItem(obstacleShape2, obstacle2, PxVec4(Vector4(0.824, 0.412, 0.118, 1.0)));


	//// Crear un obstáculo estático
	PxRigidStatic* obstacle3 = gPhysics->createRigidStatic(PxTransform(PxVec3(50.0f, 15.5f, 150.0f)));
	PxShape* obstacleShape3 = gPhysics->createShape(PxBoxGeometry(200.0f, 180.0f, 50.0f), *gMaterial);
	obstacle->attachShape(*obstacleShape3);
	RenderItem* obs3 = new RenderItem(obstacleShape3, obstacle3, PxVec4(Vector4(0.824, 0.412, 0.118, 1.0)));

	PxRigidStatic* obstacle4 = gPhysics->createRigidStatic(PxTransform(PxVec3(50.0f, 15.5f, -250.0f)));
	PxShape* obstacleShape4 = gPhysics->createShape(PxBoxGeometry(200.0f, 100.0f, 50.0f), *gMaterial);
	obstacle->attachShape(*obstacleShape4);
	RenderItem* obs4 = new RenderItem(obstacleShape4, obstacle4, PxVec4(Vector4(0.824, 0.412, 0.118, 1.0)));

	//Suelo
	PxRigidStatic* obstacle5 = gPhysics->createRigidStatic(PxTransform(PxVec3(50.0f, -100.5f, 0.0f)));
	PxShape* obstacleShape5 = gPhysics->createShape(PxBoxGeometry(300.0f, 20.0f, 300.0f), *gMaterial);
	obstacle->attachShape(*obstacleShape5);
	RenderItem* obs5 = new RenderItem(obstacleShape5, obstacle5, PxVec4(Vector4(0.565, 0.933, 0.565, 1.0)));


	PxRigidStatic* obstacle6 = gPhysics->createRigidStatic(PxTransform(PxVec3(0, 0, -80.0f)));
	PxShape* obstacleShape6 = gPhysics->createShape(PxBoxGeometry(200.0f, 2.0f, 30.0f), *gMaterial);
	obstacle->attachShape(*obstacleShape6);
	RenderItem* obs6 = new RenderItem(obstacleShape6, obstacle6, PxVec4(Vector4(0.545, 0.271, 0.075, 1.0)));

	PxRigidStatic* obstacle7 = gPhysics->createRigidStatic(PxTransform(PxVec3(50.0f, -50.5f, -80.0f)));
	PxShape* obstacleShape7 = gPhysics->createShape(PxBoxGeometry(200, 50.0f, 2), *gMaterial);
	RenderItem* obs7 = new RenderItem(obstacleShape7, obstacle7, PxVec4(Vector4(0.545, 0.271, 0.075, 1.0)));


	PxQuat rotation(-(PxPi / 6), PxVec3(0, 0, 1)); 
	PxTransform transform(PxVec3(70.0f, 150.5f, -80.0f), rotation);
	PxRigidStatic* obstacle8 = gPhysics->createRigidStatic(transform);
	PxShape* obstacleShape8 = gPhysics->createShape(PxBoxGeometry(85.0f, 2.0f, 300.0f), *gMaterial);
	obstacle8->attachShape(*obstacleShape8);
	RenderItem* obs8 = new RenderItem(obstacleShape8, obstacle8, PxVec4(Vector4(0.25f, 0.12f, 0.03f, 1.0f)));

	PxQuat rotation2(PxPi / 6, PxVec3(0, 0, 1));
	PxTransform transform2(PxVec3(-60, 150, -80), rotation2);
	PxRigidStatic* obstacle9 = gPhysics->createRigidStatic(transform2);
	PxShape* obstacleShape9 = gPhysics->createShape(PxBoxGeometry(85.0f, 2.0f, 300.0f), *gMaterial);
	obstacle9->attachShape(*obstacleShape9);
	RenderItem* obs9 = new RenderItem(obstacleShape9, obstacle9, PxVec4(Vector4(0.25f, 0.12f, 0.03f, 1.0f)));

	PxRigidStatic* obstacle10 = gPhysics->createRigidStatic(PxTransform(PxVec3(50.0f, 200.5f, 0.0f)));
	PxShape* obstacleShape10 = gPhysics->createShape(PxBoxGeometry(300.0f, 20.0f, 300.0f), *gMaterial);
	obstacle->attachShape(*obstacleShape10);
	RenderItem* obs10 = new RenderItem(obstacleShape10, obstacle10, PxVec4(Vector4(0.25f, 0.12f, 0.03f, 1.0f)));

	partSys = new ParticleSystem();

	partSys->GenerateAnchoredSpring(Vector3D<>(4.5, 150, 0));
	partSys->GenerateAnchoredSpring(Vector3D<>(4.5, 150, -20));
	partSys->GenerateAnchoredSpring(Vector3D<>(4.5, 150, -60));
	partSys->GenerateAnchoredSpring(Vector3D<>(4.5, 150, -100));
	partSys->GenerateAnchoredSpring(Vector3D<>(4.5, 150, -140));
	partSys->GenerateAnchoredSpring(Vector3D<>(4.5, 150, -180));
	


	 // Crear suelo estático
	 PxRigidStatic* ground = gPhysics->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
	 PxShape* groundShape = gPhysics->createShape(PxBoxGeometry(110.0f, 1.0f, 20.0f), *gMaterial);
	 ground->attachShape(*groundShape);
	 gScene->addActor(*ground);
	 RenderItem* suelo = new RenderItem(groundShape, ground, PxVec4(0.0, 0.9, 0.9, 1.0));

	

	 partSys->addRigidSolidGen(gPhysics, gScene, gMaterial, Vector3D<>(-100, 5, 0), Vector3D<>(0, 1, 0), 1.0f, 
		 Vector3D<>(4.0f, 4.0f, 4.0f), 1000, 4, PxVec4(Vector4(1.0f, 0.412f, 0.706f, 1.0f)), 1, PxVec3(8, 0.0, 0.0));

	 PxRigidStatic* ground2 = gPhysics->createRigidStatic(PxTransform(PxVec3(0.0f, 50.0f, 0.0f)));
	 PxShape* groundShape2 = gPhysics->createShape(PxBoxGeometry(120.0f, 1.0f, 20.0f), *gMaterial);
	 ground2->attachShape(*groundShape2);
	 gScene->addActor(*ground2);
	 RenderItem* suelo2 = new RenderItem(groundShape, ground2, PxVec4(0.0, 0.9, 0.9, 1.0));

	partSys->addRigidSolidGen(gPhysics, gScene, gMaterial, Vector3D<>(100, 55, 0), Vector3D<>(0, 1, 0), 0.5f,
		 Vector3D<>(4.0f, 4.0f, 4.0f), 1000, 5.25, PxVec4(255, 255, 0, 255), 1, PxVec3(-8, 0.0, 0.0));


	}






// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);


	gScene->simulate(t);
	gScene->fetchResults(true);

	for each (Particle* particle in particlesVector)
	{
		particle->Integrate(t);


	}

	//solid->update(t);

	partSys->Update(t);

	
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	delete partSys;

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();


	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		break;
	}
	case 'F':
	{
		PxVec3 position = GetCamera()->getTransform().p;
		PxVec3 direction = GetCamera()->getDir();

		// Crear el sólido (bola) con los parámetros deseados
			bullet = new SolidRigid(
			gPhysics, gScene, gMaterial,
			Vector3D<>(position.x, position.y, position.z), // Posición inicial
			Vector3D<>(1.0f, 1.0f, 1.0f),                  // Dimensiones (radio de la esfera)
			1.0f,                                          // Densidad
			10.0f,                                         // Tiempo de vida
			PxVec4(1.0f, 0.0f, 0.0f, 1.0f),                // Color (rojo)
			PxVec3(direction.x * 50, direction.y * 50, direction.z * 50) // Fuerza inicial
		);
			
		bulletActor = bullet->getActor();
		balaList.push_back(bullet);
		
		// Añadir una fuerza inicial para darle velocidad a la bola
		bullet->addForce(Vector3D<>(direction.x * 500, direction.y * 500, direction.z * 500));

		
		break;
	}
	//case 'G':
	//{
	//	cout << "Particle" << endl;
	//	//Gun
	//	Particle* particle = new Particle(GetCamera()->getTransform().p, 100 * GetCamera()->getDir(), PxVec3(0, 0, 0));
	//	particle->setAcel(PxVec3(0, -2, 0));
	//	particlesVector.push_back(particle);
	//	break;
	//}
	//case 'H':
	//{
	//	cout << "Particle" << endl;
	//	//Laser?
	//	Particle* particle = new Particle(GetCamera()->getTransform().p, 10000 * GetCamera()->getDir(), PxVec3(0, 0, 0));
	//	
	//	particle->setAcel(PxVec3(0, -2, 0));
	//	particlesVector.push_back(particle);
	//	break;
	//}
	//case 'J':
	//{
	//	
	//	partSys->Explosion();
	//	break;
	//}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);



	  // Verifica si actor1 o actor2 es la bala
	if (actor1 == bulletActor || actor2 == bulletActor) {
		PxActor* otherActor = (actor1 == bulletActor) ? actor2 : actor1;

			if (std::find(partSys->getGeneratedActors().begin(), partSys->getGeneratedActors().end(), otherActor)
				!= partSys->getGeneratedActors().end()) {
				// Colisión detectada
				std::cout << "Colisión con un sólido generado por un generador\n";

				// Destruye la bala y crea el sistema de partículas
				
				Vector3D<> pos = Vector3D<>(bulletActor->getGlobalPose().p.x, bulletActor->getGlobalPose().p.y, bulletActor->getGlobalPose().p.z);
				partSys->addSpark(pos, 15 , 0.1);
				score += 10;
			
			}
			for (auto it = balaList.begin(); it != balaList.end(); ) {

				if ((*it)->getActor() == bulletActor) {
					delete* it;
					it = balaList.erase(it);
				}
				else
					++it;
			}


			for (auto it = partSys->getSolidList().begin(); it != partSys->getSolidList().end(); ) {

				if ((*it)->getActor() == otherActor) {
					delete* it;
					it = partSys->getSolidList().erase(it);
				}
				else
					++it;
			}

		
		
	}
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}