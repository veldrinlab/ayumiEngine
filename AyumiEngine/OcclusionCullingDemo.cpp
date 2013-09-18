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
//static int visible;
//
//void exitDemo()
//{
//	isRunning = false;
//}
//
//void updateOcclusion()
//{
//	visible = EngineInterface::getVisibleObjects();
//	EngineInterface::updateText("Visible",lexical_cast<string>(visible));
//}
//
//void runOcclusionCullingDemo()
//{
//	isRunning = true;
//	visible = 0;
//	EngineInterface::createEngine("Data/Scripts/config.lua");
//	EngineInterface::addGameLoopTask("Occlusion",updateOcclusion);
//
//	EngineInterface::connectKeyboardAction(Escape,exitDemo);
//	EngineInterface::addRenderTask("performOcclusionQuery");
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
//	for(int i = 0; i < 3; ++i)
//	{
//		SceneEntity* box = new SceneEntity("Box","Box","Box");
//		box->initializeSceneEntity();
//		box->setEntityPosition(0.0f,0.0f,-10.0f*i);
//		EngineInterface::addEntityToScene(box);
//	}
//
//	EngineInterface::initializeFont("Font",32);
//	EngineInterface::addText("Mesage","Visible objects: ",Vector3D(-750.0f,580.0f,0.0f));
//	EngineInterface::addText("Visible",lexical_cast<string>(visible),Vector3D(-150.0f,580.0f,0.0f));
//	EngineInterface::addSprite("AyumiLogo",Vector3D(-450.0f,-500.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));
//	EngineInterface::runGameLoop(&isRunning);
//	EngineInterface::releaseEngine();
//}
