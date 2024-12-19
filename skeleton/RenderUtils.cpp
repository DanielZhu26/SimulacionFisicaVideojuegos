

#include <vector>

#include "PxPhysicsAPI.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include <iostream>
#include <string>
enum class GameState {
	MainMenu,
	Playing,
	FinalScreen
};

GameState currentState = GameState::MainMenu;
std::string gameTitle = "HIT BALL";
std::string pressEnterText = "Pulsa Enter para empezar";
std::string pressEnterText2 = "Pulsa Enter para volver al inicio";


float colorR = 1.0f, colorG = 0.0f, colorB = 0.0f;
float colorChangeSpeed = 0.5f;

float timeRemaining = 10.0f; // 90 segundos



using namespace physx;

extern void initPhysics(bool interactive);
extern void stepPhysics(bool interactive, double t);	
extern void cleanupPhysics(bool interactive);
extern void keyPress(unsigned char key, const PxTransform& camera);
extern PxPhysics* gPhysics;
extern PxMaterial* gMaterial;

std::vector<const RenderItem*> gRenderItems;

double PCFreq = 0.0;
__int64 CounterStart = 0;
__int64 CounterLast = 0;




void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		return;

	PCFreq = double(li.QuadPart) /*/ 1000.0*/;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
	CounterLast = CounterStart;
}

double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	double t = double(li.QuadPart - CounterLast) / PCFreq;
	CounterLast = li.QuadPart;
	return t;
}

namespace
{
	Camera*	sCamera;

void motionCallback(int x, int y)
{
	if (currentState == GameState::Playing) {
		sCamera->handleMotion(x, y);
	}
}

void keyboardCallback(unsigned char key, int x, int y)
{
	if(key==27)
		exit(0);

	//if(!sCamera->handleKey(key, x, y))
	//	keyPress(key, sCamera->getTransform());
	glutSetCursor(GLUT_CURSOR_NONE);
	if (key == 13) 
	{ 
		if (currentState == GameState::MainMenu) {
			currentState = GameState::Playing;
			score = 0;          // Reiniciar puntuación
			timeRemaining = 30; // Reiniciar tiempo
		}
		else if (currentState == GameState::FinalScreen) {
			currentState = GameState::MainMenu; // Volver al menú principal
		}
	}
	else if (currentState == GameState::Playing) 
	{
		keyPress(key, GetCamera()->getTransform());
	}

}

void mouseCallback(int button, int state, int x, int y)
{
	if (currentState == GameState::Playing) {
		sCamera->handleMouse(button, state, x, y);
	}
}

void idleCallback()
{
	glutPostRedisplay();
}

float stepTime = 0.0f;
//#define FIXED_STEP

void updateColor(double time) {
	colorR = (sin(colorChangeSpeed * time) + 1.0f) / 2.0f;
	colorG = (sin(colorChangeSpeed * time + 2.0f) + 1.0f) / 2.0f;
	colorB = (sin(colorChangeSpeed * time + 4.0f) + 1.0f) / 2.0f;
}

void renderCallback()
{
	double t = GetCounter();
#ifdef FIXED_STEP
	if (t < (1.0f / 30.0f))
	{
		fprintf(stderr, "Time: %f\n", stepTime);
		stepTime += t;
	}
	else
		stepTime = 1.0f / 30.0f;

	if (stepTime >= (1.0f / 30.0f))
	{
		stepPhysics(true, stepTime);
		stepTime = 0.0f;
	}
#else
	stepPhysics(true, t);
#endif

	startRender(sCamera->getEye(), PxVec3(0, 0, 1));
	updateColor(t);
	if (currentState == GameState::MainMenu) {
		// Renderizar el menú principal
		//startRender(sCamera->getEye(), PxVec3(0, 0, 1));
		drawRectangle(-200, -100, 1920, 1080, 0.2f, 0.2f, 0.2f);
		drawText2(gameTitle, 850, 600, 204, 0, 204, 0.5); // Título más grande y verde
		drawText2(pressEnterText, 825, 450, 204, 0, 204, 0.2);
		
	}
	else if (currentState == GameState::Playing)
	{
		startRender(sCamera->getEye(), sCamera->getDir());
		// Actualizar tiempo restante
		timeRemaining -= t;
		if (timeRemaining <= 0.0f) {
			currentState = GameState::FinalScreen; // Ir a la pantalla final
			timeRemaining = 0.0f; // Asegurar que no sea negativo
		}

		
		//fprintf(stderr, "Num Render Items: %d\n", static_cast<int>(gRenderItems.size()));
		for (auto it = gRenderItems.begin(); it != gRenderItems.end(); ++it)
		{
			const RenderItem* obj = (*it);
			auto objTransform = obj->transform;
			if (!objTransform)
			{
				auto actor = obj->actor;
				if (actor)
				{
					renderShape(*obj->shape, actor->getGlobalPose(), obj->color);
					continue;
				}
			}
			renderShape(*obj->shape, objTransform ? *objTransform : physx::PxTransform(PxIdentity), obj->color);
		}

		// Mostrar el tiempo restante para disparar 
		if (cooldownRemaining <= 0.0)
		{
			drawText2("Shoot!", 50, 800, 0, 255, 0, 0.2); // Texto "Shoot" en verde
		}
		else
		{
			drawText2("Cooldown: " + std::to_string((int)cooldownRemaining) + " s", 50, 800, 255, 0, 0, 0.2); // Cooldown en rojo
		}

		// Renderizar el tiempo y los puntos
		drawText2("Tiempo: " + std::to_string((int)timeRemaining), 50, 1000, 255, 255, 0, 0.2);
		drawText2("Puntos: " + std::to_string(score), 50, 900, 255, 255, 0, 0.2);
		drawCrosshair(20.0f, 255.0f, 0.0f, 0.0f);

	}
	else if (currentState == GameState::FinalScreen) {
	//	startRender(sCamera->getEye(), PxVec3(0, 0, 1));
		drawRectangle(-200, -100, 1920, 1080, 0.2f, 0.2f, 0.2f);
		drawText2("GAME OVER", 750, 600, 255, 255, 0, 0.5);
		drawText2("SCORE: " + std::to_string(score), 800, 450, 255, 255, 0, 0.4);
		drawText2(pressEnterText2, 750, 300, 200, 200, 0, 0.2);
	}

	
	//PxScene* scene;
	//PxGetPhysics().getScenes(&scene, 1);
	//PxU32 nbActors = scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);
	//if (nbActors)
	//{
	//	std::vector<PxRigidActor*> actors(nbActors);
	//	scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);
	//	renderActors(&actors[0], static_cast<PxU32>(actors.size()), true, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	//}

	finishRender();
}

void exitCallback(void)
{
	delete sCamera;
	cleanupPhysics(true);
}
}

void renderLoop()
{
	StartCounter();
	sCamera = new Camera(PxVec3(3, 70, -150), PxVec3(0, 0, 1));

	setupDefaultWindow("Simulacion Fisica Videojuegos");
	setupDefaultRenderState();

	glutIdleFunc(idleCallback);
	glutDisplayFunc(renderCallback);
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(motionCallback);
	motionCallback(0,0);

	atexit(exitCallback);

	initPhysics(true);
	glutMainLoop();
}

void RegisterRenderItem(const RenderItem* _item)
{
	gRenderItems.push_back(_item);
}

void DeregisterRenderItem(const RenderItem* _item)
{
	auto it = find(gRenderItems.begin(), gRenderItems.end(), _item);
	gRenderItems.erase(it);
}

double GetLastTime()
{
	double t = double(CounterLast - CounterStart) / PCFreq;
	return t;
}

Camera* GetCamera()
{
	return sCamera;
}

PxShape* CreateShape(const PxGeometry& geo, const PxMaterial* mat)
{
	if (mat == nullptr)
		mat = gMaterial; // Default material

	PxShape* shape = gPhysics->createShape(geo, *mat);
	return shape;
}

