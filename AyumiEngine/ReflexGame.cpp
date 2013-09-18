#include "ReflexGame.hpp"

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
using namespace AyumiEngine::AyumiDestruction;

ReflexGame::ReflexGame()
{
	isRunning = true;
	EngineInterface::createEngine("Data/ReflexGame/config.lua");
	srand(static_cast<unsigned int>(time(0)));
	score = 0.0f;
}

ReflexGame::~ReflexGame()
{
	EngineInterface::releaseEngine();
}

void ReflexGame::startGame()
{		
	initIntro();
	introState();
	initGame();
	gameState();
	initGameOverState();
	gameOverState();
}

void ReflexGame::initIntro()
{
	EngineInterface::addRenderTask("renderSprites");	
	EngineInterface::connectKeyboardAction(Escape,boost::bind(&ReflexGame::exitGame,this));
	EngineInterface::playMusicTrack("IntroTrack");
	EngineInterface::addSprite("IntroLogo",Vector3D(0.0f,0.0f,0.0f),Vector3D(800.0f,600.0f,0.0f),0.0f);
	EngineInterface::addGameLoopTask("updateIntro",boost::bind(&ReflexGame::updateIntro,this));
	introBlending = 0.0f;
	timeAccumulator = 0.0f;
	fadeOut = false;
}
	
void ReflexGame::introState()
{
	EngineInterface::runGameLoop(&isRunning,false);
	EngineInterface::deleteGameLoopTask("updateIntro");
	EngineInterface::clearRenderQueue();
	isRunning = true;
	EngineInterface::stopMusicTrack("IntroTrack");
}

void ReflexGame::updateIntro()
{
	timeAccumulator += EngineInterface::getElapsedTime();

	if(fadeOut)
		introBlending -= EngineInterface::getElapsedTime()/10;
	else
		introBlending += EngineInterface::getElapsedTime()/10;
	if(introBlending > 1.3f)
		fadeOut = true;

	EngineInterface::updateSprite("IntroLogo",Vector3D(0.0f,0.0f,0.0f),Vector3D(800.0f,600.0f,0.0f),introBlending);
	
	if(timeAccumulator > 25.0f)
		isRunning = false;
}

void ReflexGame::initGame()
{
	gameOver = false;
	targets = 5;
	fireAccumulator = 0;

	EngineInterface::deleteSprite("IntroLogo");
	EngineInterface::addUpdateTask("performFrustumCulling");
	EngineInterface::clearRenderQueue();
	EngineInterface::updateEffects("Data/ReflexGame/gameEffects.lua");
	EngineInterface::addRenderTask("renderSprites");
	EngineInterface::addGameLoopTask("ScoreUpdate",boost::bind(&ReflexGame::updateScore,this));

	camera = new FirstPersonCamera(Vector3D(0.0f,2.0f,4.0f),Vector3D(0.0f,0.0f,0.0f));
	camera->setVelocity(150.0f,150.0f,150.0f);
	EngineInterface::connectMouseMoveAction(boost::bind(&FirstPersonCamera::changeViewTarget,camera,_1,_2));
	EngineInterface::addSceneCamera(camera);
	
	SceneEntity* skyBox = new SceneEntity("Sky","Box","Skybox");
	skyBox->initializeSceneEntity();
	skyBox->setEntityScale(10000.0f,10000.0f,10000.0f);
	EngineInterface::addIndependentToScene(skyBox);

	SceneEntity* m16 = new SceneEntity("M16","M16","M16");
	m16->initializeSceneEntity();
	m16->setEntityScale(0.06f,0.06f,0.06f);
	m16->setFunctionUpdating(boost::bind(&ReflexGame::updateGun,this,_1,_2));
	EngineInterface::addEntityToScene(m16);
	
	SceneEntity* ground = new SceneEntity("Ground","Ground","Floor");
	ground->initializeSceneEntity();
	ground->setEntityPosition(0.0f,0.0f,0.0f);
	ground->setEntityScale(200.0f,1.0f,200.0f);
	EngineInterface::addEntityToScene(ground);
	
	for(int i = 0; i < targets; ++i)
	{
		FractureConnections connections;
		FractureObjects objects;

		float xPosition = CommonMath::random(-10.0f,10.0f);
		float yPosition = CommonMath::random(2.0f,10.0f);
		string name = lexical_cast<string>(i);

		SceneEntity* target1 = new SceneEntity("Target1"+name,"Target1","Target");
		target1->initializeSceneEntity();
		target1->setEntityPosition(xPosition,yPosition,-2.0f);
		target1->setEntityScale(0.25f,0.25f,0.25f);
		target1->entityPhysics.isKinematic = true;
		
		SceneEntity* target2 = new SceneEntity("Target2"+name,"Target2","Target");
		target2->initializeSceneEntity();
		target2->setEntityPosition(xPosition,yPosition,-2.0f);
		target2->setEntityScale(0.25f,0.25f,0.25f);
		target2->entityPhysics.isKinematic = true;
		
		SceneEntity* target3 = new SceneEntity("Target3"+name,"Target3","Target");
		target3->initializeSceneEntity();
		target3->setEntityPosition(xPosition,yPosition,-2.0f);
		target3->setEntityScale(0.25f,0.25f,0.25f);
		target3->entityPhysics.isKinematic = true;
		
		SceneEntity* target4 = new SceneEntity("Target4"+name,"Target4","Target");
		target4->initializeSceneEntity();
		target4->setEntityPosition(xPosition,yPosition,-2.0f);
		target4->setEntityScale(0.25f,0.25f,0.25f);
		target4->entityPhysics.isKinematic = true;
		
		EngineInterface::addEntityToScene(target1);
		EngineInterface::addEntityToScene(target2);
		EngineInterface::addEntityToScene(target3);
		EngineInterface::addEntityToScene(target4);

		target1->parent = target2;
		target1->child = target3;
		target1->leftBrother = target4;
		
		target2->parent = target1;
		target2->child = target3;
		target2->leftBrother = target4;
		
		target3->parent = target2;
		target3->child = target1;
		target3->leftBrother = target4;
		
		target4->parent = target2;
		target4->child = target3;
		target4->leftBrother = target1;

		objects.push_back(target1);
		objects.push_back(target2);
		objects.push_back(target3);
		objects.push_back(target4);

		connections.push_back(DestructibleObject(target1->entityName,target2->entityName,50.0f,50.0f));
		connections.push_back(DestructibleObject(target3->entityName,target1->entityName,50.0f,50.0f));
		connections.push_back(DestructibleObject(target4->entityName,target3->entityName,50.0f,50.0f));
		connections.push_back(DestructibleObject(target2->entityName,target1->entityName,50.0f,50.0f));
		EngineInterface::createFractureConnection(objects,connections);
	}

	EngineInterface::addStaticActor(nullptr,PLANE,0,0);
	EngineInterface::connectKeyboardAction(Escape,boost::bind(&ReflexGame::exitGame,this));
	EngineInterface::connectMouseAction(LeftButton,boost::bind(&ReflexGame::fire,this));

	EngineInterface::initializeFont("Font",32);
	EngineInterface::addSprite("AyumiLogo",Vector3D(-500.0f,-500.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));
	EngineInterface::addText("Score",lexical_cast<string>(score),Vector3D(0.0f,550.0f,0.0f));
	EngineInterface::addText("Time","Time " ,Vector3D(-200.0f,550.0f,0.0f));
	EngineInterface::addText("Targets","Targets: ",Vector3D(-700.0f,550.0f,0.0f));
	EngineInterface::addText("Targets2",lexical_cast<string>(targets),Vector3D(-400.0f,550.0f,0.0f));
	EngineInterface::addSprite("Crosshair",Vector3D(0.0f,0.0f,0.0f),Vector3D(64.0f,64.0f,0.0f));
}

void ReflexGame::gameState()
{
	EngineInterface::runGameLoop(&isRunning);
}

void ReflexGame::exitGame()
{
	isRunning = false;
	gameOver = true;
}

void ReflexGame::initGameOverState()
{
	EngineInterface::stopMusicTrack("Track");
	EngineInterface::deleteGameLoopTask("ScoreUpdate");
	EngineInterface::connectKeyboardAction(Escape,boost::bind(&ReflexGame::exitGame,this));
	isRunning = true;
	EngineInterface::clearRenderQueue();
	EngineInterface::clearScene();
	EngineInterface::updateEffects("Data/ReflexGame/effectLoad.lua");
	EngineInterface::addRenderTask("renderSprites");	
	EngineInterface::deleteText("Time");
	EngineInterface::deleteText("Score");
	EngineInterface::deleteText("Targets");
	EngineInterface::deleteText("Targets2");
	EngineInterface::deleteSprite("Crosshair");
	EngineInterface::addText("GameOver","GameOver!",Vector3D(-100.0f,0.0f,0.0f));

	if(!gameOver)
	{
		EngineInterface::addText("Win","You Win!",Vector3D(-100.0f,-50.0f,0.0f));
	    ostringstream ss;
		ss << fixed << setprecision(2) << score;
		string finalScore = ss.str();
		EngineInterface::addText("Result",finalScore,Vector3D(-50.0f,-150.0f,0.0f));
	}
	else
		EngineInterface::addText("Loose","You Loose! Try again.",Vector3D(-250.0f,-50.0f,0.0f));
}

void ReflexGame::gameOverState()
{
	EngineInterface::runGameLoop(&isRunning,false);
}


void ReflexGame::updateScore()
{
	score += EngineInterface::getElapsedTime();
    ostringstream ss;
    ss << fixed << setprecision(2) << score;
	EngineInterface::updateText("Score",ss.str());
}

void ReflexGame::updateGun(AyumiEngine::AyumiScene::SceneEntity* entity, const float elapsedTime)
{
	Vector3D entityPosition = camera->getPosition();
	Vector3D viewDirection = camera->getViewDirection();
	Vector3D strafeDirection = camera->getStrafeDirection();
	
	entityPosition[0] -= viewDirection[0] * 2.5f;
	entityPosition[1] -= viewDirection[1] * 2.5f;
	entityPosition[2] -= viewDirection[2] * 2.5f;
	
	entityPosition[0] += strafeDirection[0] * 0.8f;
	entityPosition[2] += strafeDirection[2] * 0.8f;	

	entityPosition[0] -= camera->up[0] * 0.5f;
	entityPosition[1] -= camera->up[1] * 0.5f;
	entityPosition[2] -= camera->up[2] * 0.5f;

	entity->entityState.position = entityPosition;
	entity->entityState.orientation = camera->getOrientation().inverse();	

	if(fireAccumulator > 0)
	{
		fireAccumulator--;
		Quaternion rotate(Vector3D(1.0f,0.0f,0.0f),13.0f);
		rotate *= Quaternion(Vector3D(0.0f,1.0f,0.0f),-87.0f);
		rotate *= Quaternion(Vector3D(0.0f,0.0f,1.0f),0.0f);
		entity->entityState.orientation *= rotate;
	}
	else
	{
		isFired = 0;
		Quaternion rotate(Vector3D(1.0f,0.0f,0.0f),3.0f);		
		rotate *= Quaternion(Vector3D(0.0f,1.0f,0.0f),-87.0f);
		rotate *= Quaternion(Vector3D(0.0f,0.0f,1.0f),0.0f);
		entity->entityState.orientation *= rotate;
	}
}

void ReflexGame::fire()
{
	if(isFired)
		return;

	isFired = true;
	fireAccumulator = 7;
	EngineInterface::playSoundEffect("M16");

	string name = EngineInterface::rayCastTest(camera->getPosition(),camera->getViewDirection(),1000.0f);

	if(name != "None" && name != "World Plane")
	{
		if(!EngineInterface::getEntity(name)->entityPhysics.isKinematic)
			return;

		targets--;
		if(targets == 0)
			isRunning = false;

		ostringstream ss;
	    ss << targets;
		EngineInterface::updateText("Targets2",ss.str());

		EngineInterface::getEntity(name)->entityPhysics.isKinematic = false;
		static_cast<SceneEntity*>(EngineInterface::getEntity(name)->child)->entityPhysics.isKinematic = false;
		static_cast<SceneEntity*>(EngineInterface::getEntity(name)->parent)->entityPhysics.isKinematic = false;
		static_cast<SceneEntity*>(EngineInterface::getEntity(name)->leftBrother)->entityPhysics.isKinematic = false;
		
		//EngineInterface::executeFractureDestruction(camera->getPosition(),camera->getViewDirection(),100,Vector3D(2000.0f,2000.0f,0.0f));
	}
}
