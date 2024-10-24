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

std::string display_text = "This is a test";


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

ParticleSystem* partSys;

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

	partSys = new ParticleSystem();
	partSys->setRatius(100.0f);
	//partSys->addUniPartGen(Vector3(0, 0, 0), Vector3(0, 30, 0), 30 , 20.0f, 10.0f, spawnDist::UNIFORM_SD);
	partSys->addNormalPartGen(Vector3(0, 0, 0), Vector3(0, 40, 0), 40, Vector3(10, 0.0001, 10), 5.0f, spawnDist::UNIFORM_SD);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);


	gScene->simulate(t);
	gScene->fetchResults(true);

	for each (Particle * particle in particlesVector)
	{
		particle->Integrate(t);


	}

	partSys->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);



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
		cout << "Particle" << endl;

		Particle* particle = new Particle(GetCamera()->getTransform().p, 20 * GetCamera()->getDir(), PxVec3(0, 0, 0), 1, 5);
		//Particle* particle = new Particle(PxVec3(GetCamera()->getTransform().p), PxVec3(-25, 3, -25), PxVec3(0, 0, 0));
		particle->SetAccel(PxVec3(0, -2, 0));
		particlesVector.push_back(particle);
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