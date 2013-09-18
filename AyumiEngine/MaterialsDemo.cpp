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

void exitMaterialsDemo()
{
	isRunning = false;
}

void updateEntity(SceneEntity* entity, const float elapsedTime)
{
	Vector3D rotation = entity->entityState.rotation;

	rotation[1] += elapsedTime * 50.0f;
	if(rotation[1] > 360.0f)
		rotation[1] = 0.0f;

	entity->setEntityOrientation(0.0f,rotation[1],0.0f);
}

void runMaterialsDemo()
{
	isRunning = true;
	EngineInterface::createEngine("Data/Scripts/config.lua");
	EngineInterface::addUpdateTask("performFrustumCulling");
	EngineInterface::addRenderTask("renderSprites");
	EngineInterface::connectKeyboardAction(Escape,exitMaterialsDemo);
	
	/*
	FirstPersonCamera* camera = new FirstPersonCamera(Vector3D(0.0f,1.0f,5.0f),Vector3D(0.0f,0.0f,1.0f));
	camera->setVelocity(100.0f,100.0f,100.0f);
	EngineInterface::connectKeyboardAction(W,boost::bind(&FirstPersonCamera::moveCameraForward,camera));
	EngineInterface::connectKeyboardAction(S,boost::bind(&FirstPersonCamera::moveCameraBack,camera));
	EngineInterface::connectKeyboardAction(A,boost::bind(&FirstPersonCamera::moveCameraLeft,camera));
	EngineInterface::connectKeyboardAction(D,boost::bind(&FirstPersonCamera::moveCameraRight,camera));
	EngineInterface::connectMouseMoveAction(boost::bind(&FirstPersonCamera::changeViewTarget,camera,_1,_2));
	EngineInterface::addSceneCamera(camera);
	*/

	FreeCamera* camera = new FreeCamera(Vector3D(0.0f,0.0f,0.0f),Vector3D(0.0f,0.0f,1.0f));
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

	
	SceneEntity* box2 = new SceneEntity("Box2","Box","TextureMapping");
	box2->initializeSceneEntity();
	box2->setEntityPosition(-5.0f,0.0f,-5.0f);
	box2->setFunctionUpdating(updateEntity);
	EngineInterface::addEntityToScene(box2);

	SceneEntity* box3 = new SceneEntity("Box3","Box","ParallaxMapping");
	box3->initializeSceneEntity();
	box3->setEntityPosition(-10.0f,0.0f,-10.0f);
	box3->setFunctionUpdating(updateEntity);
	EngineInterface::addEntityToScene(box3);

	//SceneEntity* sphere = new SceneEntity("Sphere","Sphere","CubeMapping");
	//sphere->initializeSceneEntity();
	//sphere->setEntityPosition(-15.0f,0.0f,-15.0f);
	//EngineInterface::addEntityToScene(sphere);

	//SceneEntity* sphere2 = new SceneEntity("Sphere2","Sphere","SphereMapping");
	//sphere2->initializeSceneEntity();
	//sphere2->setEntityPosition(-20.0f,0.0f,-20.0f);
	////EngineInterface::addEntityToScene(sphere2);

	//SceneEntity* sphere3 = new SceneEntity("Sphere3","Sphere","EnvironmentMapping");
	//sphere3->initializeSceneEntity();
	//sphere3->setEntityPosition(-25.0f,0.0f,-25.0f);
	//EngineInterface::addEntityToScene(sphere3);

	//SceneEntity* torus = new SceneEntity("Torus","Torus","CellShading");
	//torus->initializeSceneEntity();
	//torus->setEntityPosition(-30.0f,0.0f,-30.0f);
	//torus->setFunctionUpdating(updateEntity);
	//EngineInterface::addEntityToScene(torus);

	//SceneEntity* billboard = new SceneEntity("Billboard","Box","Billboard");
	//billboard->initializeSceneEntity();
	//billboard->setEntityPosition(-35.0f,0.0f,-35.0f);
	//EngineInterface::addEntityToScene(billboard);
	
	EngineInterface::initializeFont("Font",32);
	EngineInterface::addSprite("AyumiLogo",Vector3D(-500.0f,-500.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));

	EngineInterface::runGameLoop(&isRunning);
	EngineInterface::releaseEngine();
}
