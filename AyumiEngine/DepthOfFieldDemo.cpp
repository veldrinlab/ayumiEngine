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
//void exitDofDemo()
//{
//	isRunning = false;
//}
//
//void runDofDemo()
//{
//	isRunning = true;
//	EngineInterface::createEngine("Data/Scripts/config.lua");
//
//	EngineInterface::connectKeyboardAction(Escape,exitDofDemo);
//
//	EngineInterface::addUpdateTask("performFrustumCulling");
//	EngineInterface::addRenderTask("renderSprites");
//
//	FirstPersonCamera* camera = new FirstPersonCamera(Vector3D(0.0f,0.0f,5.0f),Vector3D(0.0f,0.0f,1.0f));
//	camera->setVelocity(100.0f,100.0f,100.0f);
//	EngineInterface::connectKeyboardAction(W,boost::bind(&FirstPersonCamera::moveCameraForward,camera));
//	EngineInterface::connectKeyboardAction(S,boost::bind(&FirstPersonCamera::moveCameraBack,camera));
//	EngineInterface::connectKeyboardAction(A,boost::bind(&FirstPersonCamera::moveCameraLeft,camera));
//	EngineInterface::connectKeyboardAction(D,boost::bind(&FirstPersonCamera::moveCameraRight,camera));
//	EngineInterface::connectMouseMoveAction(boost::bind(&FirstPersonCamera::changeViewTarget,camera,_1,_2));
//	EngineInterface::addSceneCamera(camera);
//	
//	SceneEntity* wall = new SceneEntity("Wall","Box","DofWall");
//	wall->initializeSceneEntity();
//	wall->setEntityPosition(0.0f,0.0f,0.0f);
//	wall->setEntityScale(20.0f,5.0f,20.0f);
//	EngineInterface::addIndependentToScene(wall);
//	
//	SceneEntity* box = new SceneEntity("Box3","Box","DofBox");
//	box->initializeSceneEntity();
//	box->setEntityPosition(10.0f,0.0f,-10.0f);
//	EngineInterface::addIndependentToScene(box);
//	
//	SceneEntity* box2 = new SceneEntity("Box3","Box","DofBox");
//	box2->initializeSceneEntity();
//	box2->setEntityPosition(-10.0f,0.0f,-10.0f);
//	EngineInterface::addIndependentToScene(box2);
//	
//	SceneEntity* box3 = new SceneEntity("Box3","Box","DofBox");
//	box3->initializeSceneEntity();
//	box3->setEntityPosition(0.0f,0.0f,10.0f);
//	EngineInterface::addIndependentToScene(box3);
//	
//	EngineInterface::initializeFont("Font",32);
//	EngineInterface::addSprite("AyumiLogo",Vector3D(-500.0f,-500.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));
//	EngineInterface::runGameLoop(&isRunning);
//	EngineInterface::releaseEngine();
//}
//
//
//
//
