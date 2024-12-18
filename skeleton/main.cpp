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
SolidRigid* ball = nullptr;

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

	 //xRenderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(0.0, 0.0, 0.0), Vector4(0.5, 0.9, 0.9, 1));
	 //yRenderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(0.0, 10.0, 0.0), Vector4(0.0, 0.0, 1, 1));
	 //zRenderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(10.0, -5.0, 0.0), Vector4(1.0, 1.0, 0.0, 1));
	 //aRenderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(0.0, -5.0, 10.0), Vector4(1, 0.0, 0.0, 1));

	//Particula MRU
	
	//Particle* particle = new Particle(PxVec3(0,0,0), PxVec3(-1, 10, 0), PxVec3(0, 0, 0));
	//particle->setAcel(PxVec3(0, 10, 0));
	//particlesVector.push_back(particle);

	//Sistemas de particulas
	
	
	//partSys->AddGaussianGenerator(Vector3D<>(20, -20, 10), Vector3D<>(1, 0, 0), 30, 5, 1);
	//partSys->addUniPartGen(Vector3D<>(0, 20, 0), Vector3D<>(-0.4, 1, 0), 10, 5, 1);
	// LLuvia viento y gravedad
	//partSys->addLluvia(Vector3D<>(0, 70, 0), 40, 10);

	// Humo
	//partSys->addSmoke(Vector3D<>(5, 0, 5), 10);
	
	// Chispas torbellino
	//partSys->addSpark(Vector3D<>(10, 0, 10), 20, 0.5);

	//Muelles
	//partSys->GenerateParticleSpring();
	//partSys->GenerateAnchoredSpring();
	//partSys->GenerateBuoyancy();

	//Solidos y rigidos
	
	/* solid = new SolidRigid(gPhysics, gScene, gMaterial, Vector3D<>(0, 15.5, 0), 
		Vector3D<>(4.0f, 4.0f, 4.0f), 10000.0f, 100, PxVec4(0.0, 0.0, 1.0, 1.0));*/

	
	partSys = new ParticleSystem();
	 // Crear suelo estático
	 PxRigidStatic* ground = gPhysics->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
	 PxShape* groundShape = gPhysics->createShape(PxBoxGeometry(110.0f, 1.0f, 20.0f), *gMaterial);
	 ground->attachShape(*groundShape);
	 gScene->addActor(*ground);
	 RenderItem* suelo = new RenderItem(groundShape, ground, PxVec4(0.0, 0.9, 0.9, 1.0));

	 //// Crear un obstáculo estático
	 //PxRigidStatic* obstacle = gPhysics->createRigidStatic(PxTransform(PxVec3(0.0f, 15.5f, 10.0f)));
	 //PxShape* obstacleShape = gPhysics->createShape(PxBoxGeometry(5.0f, 5.0f, 5.0f), *gMaterial);
	 //obstacle->attachShape(*obstacleShape);
	 //gScene->addActor(*obstacle);
	 //RenderItem* obs1 = new RenderItem(obstacleShape, obstacle, PxVec4(0.3, 0.5, 1.0, 1.0));

	 partSys->addRigidSolidGen(gPhysics, gScene, gMaterial, Vector3D<>(-100, 5, 0), Vector3D<>(0, 1, 0), 1.0f, 
		 Vector3D<>(4.0f, 4.0f, 4.0f), 100, 4, PxVec4(255, 255, 0, 255), 1, PxVec3(8, 0.0, 0.0));

	 PxRigidStatic* ground2 = gPhysics->createRigidStatic(PxTransform(PxVec3(0.0f, 50.0f, 0.0f)));
	 PxShape* groundShape2 = gPhysics->createShape(PxBoxGeometry(120.0f, 1.0f, 20.0f), *gMaterial);
	 ground2->attachShape(*groundShape2);
	 gScene->addActor(*ground2);
	 RenderItem* suelo2 = new RenderItem(groundShape, ground2, PxVec4(0.0, 0.9, 0.9, 1.0));

	partSys->addRigidSolidGen(gPhysics, gScene, gMaterial, Vector3D<>(100, 55, 0), Vector3D<>(0, 1, 0), 0.5f,
		 Vector3D<>(4.0f, 4.0f, 4.0f), 100, 5.25, PxVec4(255, 255, 0, 255), 1, PxVec3(-8, 0.0, 0.0));


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
			ball = new SolidRigid(
			gPhysics, gScene, gMaterial,
			Vector3D<>(position.x, position.y, position.z), // Posición inicial
			Vector3D<>(1.0f, 1.0f, 1.0f),                  // Dimensiones (radio de la esfera)
			1.0f,                                          // Densidad
			10.0f,                                         // Tiempo de vida
			PxVec4(1.0f, 0.0f, 0.0f, 1.0f),                // Color (rojo)
			PxVec3(direction.x * 50, direction.y * 50, direction.z * 50) // Fuerza inicial
		);

		bulletActor = ball->getActor();
		
		// Añadir una fuerza inicial para darle velocidad a la bola
		ball->addForce(Vector3D<>(direction.x * 500, direction.y * 500, direction.z * 500));

		//partSys->getSolidList().push_back(ball);
		break;
	}
	case 'G':
	{
		cout << "Particle" << endl;
		//Gun
		Particle* particle = new Particle(GetCamera()->getTransform().p, 100 * GetCamera()->getDir(), PxVec3(0, 0, 0));
		particle->setAcel(PxVec3(0, -2, 0));
		particlesVector.push_back(particle);
		break;
	}
	case 'H':
	{
		cout << "Particle" << endl;
		//Laser?
		Particle* particle = new Particle(GetCamera()->getTransform().p, 10000 * GetCamera()->getDir(), PxVec3(0, 0, 0));
		
		particle->setAcel(PxVec3(0, -2, 0));
		particlesVector.push_back(particle);
		break;
	}
	case 'J':
	{
		
		partSys->Explosion();
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);

	//PxRigidDynamic* bullet = nullptr;
	//PxRigidDynamic* target = nullptr;

	//// Determinar si uno de los actores es la bala disparada
	//if (std::find(partSys->getGeneratedActors().begin(), partSys->getGeneratedActors().end(), actor1) 
	//	!= partSys->getGeneratedActors().end() &&
	//	actor2->is<PxRigidDynamic>()) {
	//	bullet = static_cast<PxRigidDynamic*>(actor2);
	//	target = static_cast<PxRigidDynamic*>(actor1);
	//}
	//else if (std::find(partSys->getGeneratedActors().begin(), partSys->getGeneratedActors().end(), actor2)
	//	!= partSys->getGeneratedActors().end() &&
	//	actor1->is<PxRigidDynamic>()) {
	//	bullet = static_cast<PxRigidDynamic*>(actor1);
	//	target = static_cast<PxRigidDynamic*>(actor2);
	//}

	//if (bullet && target) {
	//	// Destruir la bala
	//	gScene->removeActor(*bullet);
	//	bullet->release();

	//	Vector3D<> pos = Vector3D<>(target->getGlobalPose().p.x, target->getGlobalPose().p.y, target->getGlobalPose().p.z);

	//	// Crear el sistema de partículas
	//	//partSys->addSpark(pos, 20); // Asumiendo que tienes este método
	//}

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