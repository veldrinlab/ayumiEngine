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
//
//void exitGeoModDemo()
//{
//	isRunning = false;
//}
//
//void executeDifference()
//{
//	SceneEntity* big = EngineInterface::getEntity("BigBox");
//	SceneEntity* small  = EngineInterface::getEntity("SmallBox");
//	Mesh* result = nullptr;
//
//	result = EngineInterface::executeMeshDifference(big,small);
//	if(result == nullptr)
//		return;
//
//	EngineInterface::getEntity("BigBox")->entityState.isVisible = false;
//	EngineInterface::getEntity("SmallBox")->entityState.isVisible = false;
//
//	SceneEntity* resultBox = new SceneEntity("ResultBox","Box","CsgRock");
//	resultBox->initializeSceneEntity();
//	resultBox->entityState.position = EngineInterface::getEntity("BigBox")->entityState.position;
//	EngineInterface::addEntityToScene(resultBox);
//
//	resultBox->entityGeometry.geometryMesh = result;
//	delete resultBox->entityGeometry.geomteryVbo;
//	resultBox->entityGeometry.geomteryVbo = new VertexBufferObject(*result);
//	resultBox->configureGeometryAttributes();
//}
//
//void setWireframeMode()
//{
//	glPolygonMode(GL_FRONT,GL_LINE);
//	glPolygonMode(GL_BACK,GL_LINE);
//}
//
//void setTexturedMode()
//{
//	glPolygonMode(GL_FRONT,GL_FILL);
//	glPolygonMode(GL_BACK,GL_FILL);
//}
//
//void runGeoModDemo()
//{
//	isRunning = true;
//	EngineInterface::createEngine("Data/Scripts/config.lua");
//	EngineInterface::addRenderTask("renderSprites");
//	
//	EngineInterface::connectKeyboardAction(Escape,exitGeoModDemo);
//	EngineInterface::connectKeyboardAction(E,executeDifference);
//	EngineInterface::connectKeyboardAction(R,setWireframeMode);
//	EngineInterface::connectKeyboardAction(T,setTexturedMode);
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
//	SceneEntity* bigBox = new SceneEntity("BigBox","Box","CsgRock");
//	bigBox->initializeSceneEntity();
//	bigBox->setEntityPosition(-1.0f,0.0f,0.0f);
//	EngineInterface::addEntityToScene(bigBox);
//
//	SceneEntity* smallBox = new SceneEntity("SmallBox","Box2","CsgRock");
//	smallBox->initializeSceneEntity();
//	smallBox->setEntityPosition(1.0f,0.0f,0.0f);
//	EngineInterface::addEntityToScene(smallBox);
//
//	EngineInterface::initializeFont("Font",32);
//	EngineInterface::addSprite("AyumiLogo",Vector3D(-500.0f,-500.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));
//	EngineInterface::addText("Instruction","Press E to execute CSG demo",Vector3D(-650.0f,580.0f,0.0f));
//	EngineInterface::addText("Instruction","Press R to set Wireframe mode",Vector3D(-650.0f,530.0f,0.0f));
//	EngineInterface::addText("Instruction","Press T to set Textured mode",Vector3D(-650.0f,480.0f,0.0f));
//
//	EngineInterface::runGameLoop(&isRunning);
//	EngineInterface::releaseEngine();	
//}
