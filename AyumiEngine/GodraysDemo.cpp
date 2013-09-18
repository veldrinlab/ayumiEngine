//#include "AyumiDemo.hpp"
//#include "AyumiEngine/EngineInterface.hpp"
//
//using namespace std;
//using namespace boost;
//using namespace AyumiEngine;
//using namespace AyumiEngine::AyumiCore;
//using namespace AyumiEngine::AyumiInput;
//using namespace AyumiEngine::AyumiRenderer;
//using namespace AyumiEngine::AyumiResource;
//using namespace AyumiEngine::AyumiUtils;
//using namespace AyumiEngine::AyumiScene;
//using namespace AyumiEngine::AyumiMath;
//using namespace AyumiEngine::AyumiSound;
//using namespace AyumiEngine::AyumiPhysics;
//
//static bool isRunning;
//
//void exitGodRaysDemo()
//{
//	isRunning = false;
//}
//
//void updateBox(SceneEntity* entity, const float elapsedTime)
//{
//	Vector3D rotation = entity->entityState.rotation;
//
//	rotation[1] += elapsedTime * 50.0f;
//	if(rotation[1] > 360.0f)
//		rotation[1] = 0.0f;
//
//	entity->setEntityOrientation(0.0f,rotation[1],0.0f);
//}
//
//void runGodRaysDemo()
//{
//	isRunning = true;
//	EngineInterface::createEngine("Data/Scripts/config.lua");
//	EngineInterface::addUpdateTask("performFrustumCulling");
//	EngineInterface::addRenderTask("renderSprites");
//	EngineInterface::connectKeyboardAction(Escape,exitGodRaysDemo);
//
//	FirstPersonCamera* camera = new FirstPersonCamera(Vector3D(0.0f,0.0f,8.0f),Vector3D(0.0f,0.0f,1.0f));
//	camera->setVelocity(100.0f,100.0f,100.0f);
//	EngineInterface::connectKeyboardAction(W,boost::bind(&FirstPersonCamera::moveCameraForward,camera));
//	EngineInterface::connectKeyboardAction(S,boost::bind(&FirstPersonCamera::moveCameraBack,camera));
//	EngineInterface::connectKeyboardAction(A,boost::bind(&FirstPersonCamera::moveCameraLeft,camera));
//	EngineInterface::connectKeyboardAction(D,boost::bind(&FirstPersonCamera::moveCameraRight,camera));
//	EngineInterface::addSceneCamera(camera);
//	
//	SceneEntity* box = new SceneEntity("Box","Box","TextureMapping");
//	box->initializeSceneEntity();
//	box->setEntityPosition(0.0f,0.0f,4.0f);
//	box->setFunctionUpdating(updateBox);
//	EngineInterface::addEntityToScene(box);
//
//	EngineInterface::initializeFont("Font",32);
//	EngineInterface::addSprite("AyumiLogo",Vector3D(-500.0f,-500.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));
//
//	EngineInterface::runGameLoop(&isRunning);
//	EngineInterface::releaseEngine();
//}
