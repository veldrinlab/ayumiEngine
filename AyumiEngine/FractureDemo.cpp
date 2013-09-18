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
//using namespace AyumiEngine::AyumiDestruction;
//
//static bool isRunning;
//bool isFired;;
//int fireAccumulator;
//
//void updateGun(AyumiEngine::AyumiScene::SceneEntity* entity, const float elapsedTime)
//{
//	FirstPersonCamera* camera = static_cast<FirstPersonCamera*>(EngineInterface::getCamera());
//	Vector3D entityPosition = camera->getPosition();
//	Vector3D viewDirection = camera->getViewDirection();
//	Vector3D strafeDirection = camera->getStrafeDirection();
//	
//	entityPosition[0] -= viewDirection[0] * 2.5f;
//	entityPosition[1] -= viewDirection[1] * 2.5f;
//	entityPosition[2] -= viewDirection[2] * 2.5f;
//	
//	entityPosition[0] += strafeDirection[0] * 0.8f;
//	entityPosition[2] += strafeDirection[2] * 0.8f;	
//
//	entityPosition[0] -= camera->up[0] * 0.5f;
//	entityPosition[1] -= camera->up[1] * 0.5f;
//	entityPosition[2] -= camera->up[2] * 0.5f;
//
//	entity->entityState.position = entityPosition;
//	entity->entityState.orientation = camera->getOrientation().inverse();	
//
//	if(fireAccumulator > 0)
//	{
//		fireAccumulator--;
//		Quaternion rotate(Vector3D(1.0f,0.0f,0.0f),13.0f);
//		rotate *= Quaternion(Vector3D(0.0f,1.0f,0.0f),-87.0f);
//		rotate *= Quaternion(Vector3D(0.0f,0.0f,1.0f),0.0f);
//		entity->entityState.orientation *= rotate;
//	}
//	else
//	{
//		isFired = 0;
//		Quaternion rotate(Vector3D(1.0f,0.0f,0.0f),3.0f);		
//		rotate *= Quaternion(Vector3D(0.0f,1.0f,0.0f),-87.0f);
//		rotate *= Quaternion(Vector3D(0.0f,0.0f,1.0f),0.0f);
//		entity->entityState.orientation *= rotate;
//	}
//}
//
//void exitFractureDemo()
//{
//	isRunning = false;
//}
//
//void fire()
//{
//	if(isFired)
//		return;
//
//	isFired = true;
//	fireAccumulator = 7;
//	EngineInterface::playSoundEffect("M16");
//	Camera* camera = EngineInterface::getCamera();
//	EngineInterface::executeFractureDestruction(camera->getPosition(),camera->getViewDirection(),100,Vector3D(2000.0f,2000.0f,0.0f));
//}
//
//void runFractureDemo()
//{
//	isRunning = true;
//	isFired = false;
//	fireAccumulator = 0;
//
//	EngineInterface::createEngine("Data/Scripts/config.lua");
//	EngineInterface::addUpdateTask("performFrustumCulling");
//	EngineInterface::addRenderTask("renderSprites");
//
//	EngineInterface::connectKeyboardAction(Escape,exitFractureDemo);
//	EngineInterface::connectMouseAction(LeftButton,fire);
//
//	FirstPersonCamera* camera = new FirstPersonCamera(Vector3D(0.0f,10.0f,40.0f),Vector3D(0.0f,0.0f,-1.0f));
//	camera->setVelocity(100.0f,100.0f,100.0f);
//	EngineInterface::connectKeyboardAction(W,boost::bind(&FirstPersonCamera::moveCameraForward,camera));
//	EngineInterface::connectKeyboardAction(S,boost::bind(&FirstPersonCamera::moveCameraBack,camera));
//	EngineInterface::connectKeyboardAction(A,boost::bind(&FirstPersonCamera::moveCameraLeft,camera));
//	EngineInterface::connectKeyboardAction(D,boost::bind(&FirstPersonCamera::moveCameraRight,camera));
//	EngineInterface::connectMouseMoveAction(boost::bind(&FirstPersonCamera::changeViewTarget,camera,_1,_2));
//	EngineInterface::addSceneCamera(camera);
//	
//	SceneEntity* m16 = new SceneEntity("M16","M16","M16");
//	m16->initializeSceneEntity();
//	m16->setEntityScale(0.06f,0.06f,0.06f);
//	m16->setFunctionUpdating(boost::bind(updateGun,_1,_2));
//	EngineInterface::addEntityToScene(m16);
//	
//	SceneEntity* skyBox = new SceneEntity("Sky","Box","Skybox");
//	skyBox->initializeSceneEntity();
//	skyBox->setEntityScale(10000.0f,10000.0f,10000.0f);
//	EngineInterface::addIndependentToScene(skyBox);
//
//	SceneEntity* ground = new SceneEntity("Ground","Ground","Floor");
//	ground->initializeSceneEntity();
//	ground->setEntityPosition(0.0f,0.0f,0.0f);
//	ground->setEntityScale(200.0f,1.0f,200.0f);
//	EngineInterface::addEntityToScene(ground);
//
//	FractureConnections connections[5];
//	FractureObjects objects[5];
//	FractureConnections connections2[5];
//	FractureObjects objects2[5];
//	SceneEntity* wall = nullptr;
//	SceneEntity* wall2 = nullptr;
//	SceneEntity* wall3 = nullptr;
//	SceneEntity* wall4 = nullptr;
//	
//	for(int i = 0; i < 5; i++)
//	{
//		string id = boost::lexical_cast<string>(i);
//		wall = new SceneEntity("Wall"+id,"Fracture1","Fracture");
//		wall->initializeSceneEntity();
//		wall->setEntityPosition(i*20.0f,4.0f,0.0f);
//		EngineInterface::addEntityToScene(wall);
//
//		wall2 = new SceneEntity("Wall2"+id,"Fracture2","Fracture");
//		wall2->initializeSceneEntity();
//		wall2->setEntityPosition(i*20.0f,4.0f,0.0f);
//		EngineInterface::addEntityToScene(wall2);
//	
//		wall3 = new SceneEntity("Wall3"+id,"Fracture3","Fracture");
//		wall3->initializeSceneEntity();
//		wall3->setEntityPosition(i*20.0f,4.0f,0.0f);
//		EngineInterface::addEntityToScene(wall3);
//
//		wall4 = new SceneEntity("Wall4"+id,"Fracture4","Fracture");
//		wall4->initializeSceneEntity();
//		wall4->setEntityPosition(i*20.0f,4.0f,0.0f);
//		EngineInterface::addEntityToScene(wall4);
//
//		objects[i].push_back(wall);
//		objects[i].push_back(wall2);
//		objects[i].push_back(wall3);
//		objects[i].push_back(wall4);
//
//		connections[i].push_back(DestructibleObject(wall->entityName,wall2->entityName,50.0f,50.0f));
//		connections[i].push_back(DestructibleObject(wall3->entityName,wall->entityName,50.0f,50.0f));
//		connections[i].push_back(DestructibleObject(wall4->entityName,wall3->entityName,50.0f,50.0f));
//		connections[i].push_back(DestructibleObject(wall2->entityName,wall->entityName,50.0f,50.0f));
//
//		EngineInterface::createFractureConnection(objects[i],connections[i]);
//	}
//
//	for(int i = 0; i < 5; i++)
//	{
//		string id = boost::lexical_cast<string>(i) + "a";
//		wall = new SceneEntity("Wall"+id,"Fracture1","Fracture");
//		wall->initializeSceneEntity();
//		wall->setEntityPosition(i*20.0f,10.0f,0.0f);
//		EngineInterface::addEntityToScene(wall);
//
//		wall2 = new SceneEntity("Wall2"+id,"Fracture2","Fracture");
//		wall2->initializeSceneEntity();
//		wall2->setEntityPosition(i*20.0f,10.0f,0.0f);
//		EngineInterface::addEntityToScene(wall2);
//	
//		wall3 = new SceneEntity("Wall3"+id,"Fracture3","Fracture");
//		wall3->initializeSceneEntity();
//		wall3->setEntityPosition(i*20.0f,10.0f,0.0f);
//		EngineInterface::addEntityToScene(wall3);
//
//		wall4 = new SceneEntity("Wall4"+id,"Fracture4","Fracture");
//		wall4->initializeSceneEntity();
//		wall4->setEntityPosition(i*20.0f,10.0f,0.0f);
//		EngineInterface::addEntityToScene(wall4);
//
//		objects2[i].push_back(wall);
//		objects2[i].push_back(wall2);
//		objects2[i].push_back(wall3);
//		objects2[i].push_back(wall4);
//
//		connections2[i].push_back(DestructibleObject(wall->entityName,wall2->entityName,50.0f,50.0f));
//		connections2[i].push_back(DestructibleObject(wall3->entityName,wall->entityName,50.0f,50.0f));
//		connections2[i].push_back(DestructibleObject(wall4->entityName,wall3->entityName,50.0f,50.0f));
//		connections2[i].push_back(DestructibleObject(wall2->entityName,wall->entityName,50.0f,50.0f));
//
//		EngineInterface::createFractureConnection(objects2[i],connections2[i]);
//	}
//
//	EngineInterface::addStaticActor(nullptr,PLANE,0,0);
//	EngineInterface::initializeFont("Font",32);
//	EngineInterface::addSprite("AyumiLogo",Vector3D(-500.0f,-500.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));
//	EngineInterface::addSprite("Crosshair",Vector3D(0.0f,0.0f,0.0f),Vector3D(64.0f,64.0f,0.0f));
//
//	EngineInterface::runGameLoop(&isRunning);
//	EngineInterface::releaseEngine();
//}
