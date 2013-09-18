#include "AyumiDemo.hpp"
#include "AyumiEngine/EngineInterface.hpp"

using namespace std;
using namespace boost;
using namespace AyumiEngine;
using namespace AyumiEngine::AyumiCore;
using namespace AyumiEngine::AyumiInput;
using namespace AyumiEngine::AyumiRenderer;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiUtils;
using namespace AyumiEngine::AyumiScene;
using namespace AyumiEngine::AyumiMath;
using namespace AyumiEngine::AyumiSound;
using namespace AyumiEngine::AyumiPhysics;

static bool isRunning;
static int visible;

void exitFrustumDemo()
{
	isRunning = false;
}

void updateFrustum()
{
	visible = EngineInterface::getVisibleObjects();
	EngineInterface::updateText("Visible",lexical_cast<string>(visible));
}

void runFrustumCullingDemo()
{
	isRunning = true;
	visible = 0;
	EngineInterface::createEngine("Data/Scripts/config.lua");
	EngineInterface::addGameLoopTask("Frustum",updateFrustum);

	EngineInterface::connectKeyboardAction(Escape,exitFrustumDemo);
	EngineInterface::addUpdateTask("performFrustumCulling");
	EngineInterface::addRenderTask("renderSprites");

	FreeCamera* camera = new FreeCamera(Vector3D(50.0f,50.0f,50.0f),Vector3D(0.0f,0.0f,1.0f));
	camera->setVelocity(100.0f,100.0f,100.0f);
	camera->setRotateVelocity(10.0f,10.0f,10.0f);
	EngineInterface::connectKeyboardAction(W,boost::bind(&FreeCamera::moveCameraForward,camera));
	EngineInterface::connectKeyboardAction(S,boost::bind(&FreeCamera::moveCameraBack,camera));
	EngineInterface::connectKeyboardAction(A,boost::bind(&FreeCamera::rotateCameraLeft,camera));
	EngineInterface::connectKeyboardAction(D,boost::bind(&FreeCamera::rotateCameraRight,camera));
	EngineInterface::connectKeyboardAction(Q,boost::bind(&FreeCamera::moveCameraUp,camera));
	EngineInterface::connectKeyboardAction(E,boost::bind(&FreeCamera::moveCameraDown,camera));
	EngineInterface::connectMouseMoveAction(boost::bind(&FreeCamera::changeViewTarget,camera,_1,_2));
	EngineInterface::addSceneCamera(camera);

	for(int i = 0; i < 10; ++i)
	{
		for(int j = 0; j < 10; ++j)
		{
			for(int k = 0; k < 10; ++k)
			{
				SceneEntity* box = new SceneEntity("Box","Box","Box");
				box->initializeSceneEntity();
				box->setEntityPosition(10.0f*i,10.0f*j,10.0f*k);
				EngineInterface::addEntityToScene(box);
			}
		}
	}
	
	EngineInterface::initializeFont("Font",32);
	EngineInterface::addText("Message","Visible objects: ",Vector3D(-750.0f,560.0f,0.0f));
	EngineInterface::addText("Visible",lexical_cast<string>(visible),Vector3D(-150.0f,560.0f,0.0f));
	EngineInterface::addSprite("AyumiLogo",Vector3D(-450.0f,-500.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));

	EngineInterface::runGameLoop(&isRunning);
	EngineInterface::releaseEngine();
}
