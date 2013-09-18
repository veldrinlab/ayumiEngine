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
using namespace AyumiEngine::AyumiDestruction;

static bool isRunning;
DestructibleTerrain* destruction;
bool collision;

class Missile : public SceneEntity
{
public:
	Vector3D moveDirection;
	bool isFired;

	Missile(const string& entityName, const string& meshName, const string& materialName) : SceneEntity(entityName,meshName,materialName)
	{
		isFired = false;
	}
	~Missile() {}

	void updateEntity(const float elapsedTime)
	{
		if(isFired)
		{
			entityState.isVisible = true;
			Vector3D entityPosition = entityState.position;
			entityPosition[0] -= moveDirection[0] * entityPhysics.velocity[0] * elapsedTime;
			entityPosition[1] -= moveDirection[1] * entityPhysics.velocity[1] * elapsedTime;
			entityPosition[2] -= moveDirection[2] * entityPhysics.velocity[2] * elapsedTime;	
			entityState.position = entityPosition;
		}
	}
};

struct CollisionFilter
{
	enum Enum
	{
		AIRCRAFT = (1 << 0),
		MISSILE = (1 << 1),
		TERRAIN = (1 << 2)
	};
};

void updateTerrain()
{
	Missile* missile = static_cast<Missile*>(EngineInterface::getEntity("Missile"));
	if(collision && missile->isFired)
	{
		EngineInterface::playSoundEffect("Explosion");
		EngineInterface::executeTerrainDestruction(destruction,missile->entityState.position,1,100.0f);
		missile->isFired = false;
		missile->entityState.isVisible = false;
		missile->entityState.position.set(0.0f,5000.0f,0.0f);
		collision = false;
	}
}

void updateFlight(SceneEntity* entity, const float elapsedTime)
{
	Vector3D entityPosition = EngineInterface::getCamera()->getPosition();
	entityPosition -= EngineInterface::getCamera()->getViewDirection()*50.0f;
	entityPosition[1] -= 10.0f;
	entity->entityState.position = entityPosition;

	Quaternion rotate(Vector3D(1.0f,0.0f,0.0f),-90.0f);
	rotate *= Quaternion(Vector3D(0.0f,1.0f,0.0f),0.0f);
	rotate *= Quaternion(Vector3D(0.0f,0.0f,1.0f),0.0f);

	entity->entityState.orientation = EngineInterface::getCamera()->getOrientation().inverse();		
	entity->entityState.orientation *= rotate;

	Vector3D cameraPosition =  EngineInterface::getCamera()->getPosition();
	cameraPosition[0] -= EngineInterface::getCamera()->getViewDirection()[0] * entity->entityPhysics.velocity[0] * elapsedTime;
	cameraPosition[1] -= EngineInterface::getCamera()->getViewDirection()[1] * entity->entityPhysics.velocity[1] * elapsedTime;
	cameraPosition[2] -= EngineInterface::getCamera()->getViewDirection()[2] * entity->entityPhysics.velocity[2] * elapsedTime;
	EngineInterface::getCamera()->setPosition(cameraPosition[0],cameraPosition[1],cameraPosition[2]);
}

void missileCollision()
{
	collision = true;
}

void flightCollision()
{
	EngineInterface::playSoundEffect("Explosion");
	isRunning = false;
}

void fireMissile()
{
	Missile* missile = static_cast<Missile*>(EngineInterface::getEntity("Missile"));
	EngineInterface::playSoundEffect("Laser");
	Vector3D missilePosition = EngineInterface::getEntity("F16")->entityState.position;
	missilePosition -= EngineInterface::getCamera()->getViewDirection() * 55.0f;	
	missile->setEntityPosition(missilePosition[0],missilePosition[1],missilePosition[2]);
	missile->entityState.orientation = EngineInterface::getCamera()->getOrientation().inverse();
	missile->moveDirection = EngineInterface::getCamera()->getViewDirection();
	missile->isFired = true;
	missile->entityState.isVisible = true;
}

void exitTerrainDestructionDemo()
{
	isRunning = false;
}

void runTerrainDestructionDemo()
{
	isRunning = true;
	EngineInterface::createEngine("Data/Scripts/config.lua");
	EngineInterface::addRenderTask("renderSprites");
	EngineInterface::addUpdateTask("performFrustumCulling");
	EngineInterface::addGameLoopTask("updateTerrain",updateTerrain);

	EngineInterface::connectKeyboardAction(Escape,exitTerrainDestructionDemo);
	EngineInterface::connectMouseAction(LeftButton,fireMissile);

	FlightCamera* camera = new FlightCamera(Vector3D(0.0f,2000.0f,0.0f),Vector3D(0.0f,0.0f,-1.0f));
	EngineInterface::connectKeyboardAction(W,boost::bind(&FlightCamera::moveCameraForward,camera));
	EngineInterface::connectMouseMoveAction(boost::bind(&FlightCamera::changeViewTarget,camera,_1,_2));
	EngineInterface::addSceneCamera(camera);

	SceneEntity* terrain = new SceneEntity("Terrain","Terrain","Terrain");
	terrain->initializeSceneEntity();
	terrain->setEntityPosition(-128.0f*50.0f,0.0f,-128.0f*50.0f);
	EngineInterface::addIndependentToScene(terrain);

	SceneEntity* skyDome = new SceneEntity("Sky","SkyDome","SkyDome");
	skyDome->initializeSceneEntity();
	skyDome->setEntityOrientation(-90.0f,0.0f,0.0f);
	skyDome->setEntityScale(10000.0f,10000.0f,10000.0f);
	EngineInterface::addIndependentToScene(skyDome);
	
	SceneEntity* flight = new SceneEntity("F16","F16","F16");
	flight->initializeSceneEntity();
	flight->setEntityScale(0.1f,0.1f,0.1f);
	flight->setEntityPosition(0.0f,1600.0f,-10.0f);
	flight->setEntityOrientation(0.0f,180.0f,180.0f);
	flight->setFunctionUpdating(updateFlight);
	flight->entityPhysics.velocity.set(20.0f,20.0f,20.0f);
	flight->entityPhysics.isKinematic = true;
	EngineInterface::addEntityToScene(flight);
	
	Missile* missile = new Missile("Missile","Missile","Missile");
	missile->initializeSceneEntity();
	missile->setEntityScale(20.0f,20.0f,20.0f);
	missile->setExtendingUpdating();
	missile->entityPhysics.isKinematic = true;
	missile->entityPhysics.velocity.set(200.0f,200.0f,200.0f);
	EngineInterface::addEntityToScene(missile);
	
	EngineInterface::initializeFont("Font",32);
	EngineInterface::addSprite("AyumiLogo",Vector3D(-500.0f,-500.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));
	EngineInterface::addSprite("Crosshair",Vector3D(0.0f,0.0f,0.0f),Vector3D(64.0f,64.0f,0.0f));

	EngineInterface::addDynamicActor(flight,BOX,CollisionFilter::AIRCRAFT,CollisionFilter::TERRAIN);
	EngineInterface::addDynamicActor(missile,BOX,CollisionFilter::MISSILE,CollisionFilter::TERRAIN);
	EngineInterface::addCollisionCallback("F16","Terrain",flightCollision);
	EngineInterface::addCollisionCallback("Missile","Terrain",missileCollision);
	destruction = EngineInterface::createDestructibleTerrain(terrain,"Data/Mesh/terrainDemo.raw",Vector4D(256.0,50.0,50.0,1500.0),CollisionFilter::TERRAIN,CollisionFilter::MISSILE | CollisionFilter::AIRCRAFT);

	EngineInterface::runGameLoop(&isRunning);
	EngineInterface::releaseDestructibleTerrain(destruction);
	EngineInterface::releaseEngine();	
}
