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
//void exitSMDemo()
//{
//	isRunning = false;
//}
//
//void runSMDemo()
//{
//	isRunning = true;
//	EngineInterface::createEngine("Data/Scripts/config.lua");
//	EngineInterface::connectKeyboardAction(Escape,exitSMDemo);
//
//	EngineInterface::addUpdateTask("performFrustumCulling");
//	EngineInterface::addRenderTask("renderSprites");
//	EngineInterface::addRenderTask("renderShadows");
//
//	FirstPersonCamera* camera = new FirstPersonCamera(Vector3D(-5.0f,5.0f,10.0),Vector3D(0.0,0.0,0.0));
//	camera->setVelocity(100.0f,100.0f,100.0f);
//	EngineInterface::connectKeyboardAction(W,boost::bind(&FirstPersonCamera::moveCameraForward,camera));
//	EngineInterface::connectKeyboardAction(S,boost::bind(&FirstPersonCamera::moveCameraBack,camera));
//	EngineInterface::connectKeyboardAction(A,boost::bind(&FirstPersonCamera::moveCameraLeft,camera));
//	EngineInterface::connectKeyboardAction(D,boost::bind(&FirstPersonCamera::moveCameraRight,camera));
//	EngineInterface::connectMouseMoveAction(boost::bind(&FirstPersonCamera::changeViewTarget,camera,_1,_2));
//	EngineInterface::addSceneCamera(camera);
//	
//	SceneEntity* ground = new SceneEntity("Ground","Box","ShadowFloor");
//	ground->initializeSceneEntity();
//	ground->setEntityPosition(0.0f, -4.0f, 0.0f);
//	ground->setEntityScale(10.0f,0.4f,10.0f);
//	ground->setEntityOrientation(0.0f,0.0,0.0f);
//	EngineInterface::addEntityToScene(ground);
//	
//	SceneEntity* box = new SceneEntity("Box3","Box","Box");
//	box->initializeSceneEntity();
//	box->setEntityPosition(3.0f,-1.0f,0.0f);
//	box->setEntityOrientation(0.0f,0.0f,0.0f);
//	EngineInterface::addEntityToScene(box);
//	
//	SceneEntity* box2 = new SceneEntity("Box3","Box","Box");
//	box2->initializeSceneEntity();
//	box2->setEntityPosition(0.0f,-1.0f,2.0f);
//	EngineInterface::addEntityToScene(box2);
//	
//	SceneEntity* box3 = new SceneEntity("Box3","Box","Box");
//	box3->initializeSceneEntity();
//	box3->setEntityPosition(4.0f,-1.0f,-2.0f);
//	EngineInterface::addEntityToScene(box3);
//
//	EngineInterface::updateShadowSource(0,Vector3D(0.0,10.0f,0.0f),Vector3D(90.0f,0.0f,0.0f));
//	EngineInterface::initializeFont("Font",32);
//	EngineInterface::addSprite("AyumiLogo",Vector3D(-500.0f,-500.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));
//	EngineInterface::runGameLoop(&isRunning);
//	EngineInterface::releaseEngine();
//}
