#include "SprintGame.hpp"

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

SprintGame::SprintGame()
{
	isRunning = true;
	EngineInterface::createEngine("Data/SprintGame/config.lua");
	srand(static_cast<unsigned int>(time(0)));
	score = 0.0f;
}

SprintGame::~SprintGame()
{
	EngineInterface::releaseEngine();
}

// integracja O'Neil

void SprintGame::controlDayTime() {
	timeUpdate = !timeUpdate;
}

void SprintGame::updateSunLight() {

	if(timeUpdate) {
		sunTimeAccumulator += EngineInterface::getElapsedTime()/2;

		PointLight* light = EngineInterface::getPointLight(0);

		float radius = 10000.0f;
		float lightRadius = 12500.0f;
		light->position[0] = sin(CommonMath::PI*sunTimeAccumulator)*radius;
		light->position[1] = cos(CommonMath::PI*sunTimeAccumulator)*radius;

		light->radius = max(0.0f,7500.0f+cos(CommonMath::PI*sunTimeAccumulator)*lightRadius);
	}
}

void SprintGame::updateONeil(EntityMaterial* material, const float deltaTime) {
	if(timeUpdate) {
		cout << "O'Neil update" << endl;
		material->vectors["lightDirection"][0] = sin(CommonMath::PI*sunTimeAccumulator);
		material->vectors["lightDirection"][1] = cos(CommonMath::PI*sunTimeAccumulator);
	}
}

void SprintGame::startGame()
{		
	initIntro();
	introState();
	initGame();
	gameState();
	initGameOverState();
	gameOverState();
}

void SprintGame::initIntro()
{
	EngineInterface::addRenderTask("renderSprites");	
	EngineInterface::connectKeyboardAction(Escape,boost::bind(&SprintGame::exitGame,this));
	EngineInterface::playMusicTrack("IntroTrack");
	EngineInterface::addSprite("IntroLogo",Vector3D(0.0f,0.0f,0.0f),Vector3D(800.0f,600.0f,0.0f),0.0f);
	EngineInterface::addGameLoopTask("updateIntro",boost::bind(&SprintGame::updateIntro,this));
	introBlending = 0.0f;
	timeAccumulator = 0.0f;
	fadeOut = false;
}
	
void SprintGame::introState()
{
	EngineInterface::runGameLoop(&isRunning,false);
	EngineInterface::deleteGameLoopTask("updateIntro");
	EngineInterface::clearRenderQueue();
	isRunning = true;
	EngineInterface::stopMusicTrack("IntroTrack");
}

void SprintGame::updateIntro()
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

void SprintGame::initGame()
{
	gameOver = false;
	lifeAmount = 3;
	EngineInterface::deleteSprite("IntroLogo");
	EngineInterface::addUpdateTask("performFrustumCulling");
	EngineInterface::clearRenderQueue();
	EngineInterface::updateEffects("Data/SprintGame/gameEffects.lua");
	EngineInterface::addRenderTask("renderParticles");
	EngineInterface::addRenderTask("renderSprites");
	EngineInterface::addRenderTask("renderShadows");
	EngineInterface::addGameLoopTask("ScoreUpdate",boost::bind(&SprintGame::updateScore,this));

	camera = new FirstPersonCamera(Vector3D(0.0f,1.75f,1.0f),Vector3D(10.0f,0.0f,0.0f));
	EngineInterface::addSceneCamera(camera);

	// O'Neil sky
	timeUpdate = false;
	sunTimeAccumulator = 0.0f;
	EngineInterface::addGameLoopTask("updateSunLight",boost::bind(&SprintGame::updateSunLight,this));

	sky = new SceneEntity("Sky","Sphere","ONeil");
	sky->initializeSceneEntity();

	//to moze zbedne
	sky->setEntityScale(1000.0f,1000.0f,1000.0f);
	sky->setEntityOrientation(0.0f,90.0f,0.0f);
	sky->setEntityPosition(0.0f,-1000.0f,0.0f);
	EngineInterface::addIndependentToScene(sky);
	
	// init oneil
	EngineInterface::addMaterialUpdateFunction("oneil",boost::bind(&SprintGame::updateONeil,this,_1,_2));
	EngineInterface::connectKeyboardAction(U,boost::bind(&SprintGame::controlDayTime,this));


	vehicle = new SceneEntity("Vehicle","Vehicle","Vehicle");
	vehicle->initializeSceneEntity();
	vehicle->entityPhysics.isKinematic = true;
	vehicle->setEntityPosition(0.0f,1.25f,0.0f);
	vehicle->setEntityOrientation(-90.0f,0.0f,0.0f);
	acceleration.set(0.75f,0.75f,1.5f);
	vehicle->setFunctionUpdating(boost::bind(&SprintGame::updateVehicle,this,_1,_2));
	EngineInterface::addEntityToScene(vehicle);
	EngineInterface::addDynamicActor(vehicle,BOX,Collision::VEHICLE,Collision::BOX);

	for(int i = 0; i < 200; ++i)
	{
		SceneEntity* c = new SceneEntity("Course"+i,"Course1","Course");
		c->initializeSceneEntity();
		c->entityPhysics.isKinematic = false;
		c->setEntityPosition(0.0f,1.0f,-i*4.0f);
		c->setEntityOrientation(-90.0f,0.0f,0.0f);
		c->setEntityScale(4.0f,2.0f,2.0f);
		EngineInterface::addEntityToScene(c);
		course.push_back(c);
	}

	terrain = new SceneEntity("Terrain","Terrain","Terrain");
	terrain->initializeSceneEntity();
	terrain->setEntityPosition(-128.0f*50,-700.0f,-128.0f*50);
	EngineInterface::addIndependentToScene(terrain);
	
	for(int i = 0; i < 50; ++i)
	{
		int courseID = static_cast<int>(CommonMath::random(3.0f,120.0f));
		float xPosition = CommonMath::random(-3.5f,3.5f);

		string name = "Box";
		name += lexical_cast<string>(i);
		SceneEntity* box = new SceneEntity(name,"Box","Box");

		box->initializeSceneEntity();
		box->setEntityPosition(xPosition,1.0f, courseID*-4.0f);
		box->setEntityScale(0.25f,0.25f,0.25f);
		EngineInterface::addEntityToScene(box);
		EngineInterface::addDynamicActor(box,BOX,Collision::BOX,Collision::VEHICLE);
		EngineInterface::addCollisionCallback("Vehicle",name,boost::bind(&SprintGame::collisionCallback,this));
		EngineInterface::addCollisionCallback(name,"Vehicle",boost::bind(&SprintGame::collisionCallback,this));
	}

	EngineInterface::addStaticActor(nullptr,PLANE,0,0);
	EngineInterface::connectKeyboardAction(Escape,boost::bind(&SprintGame::exitGame,this));
	EngineInterface::connectKeyboardAction(W,boost::bind(&SprintGame::accelerate,this));
	EngineInterface::connectKeyboardAction(A,boost::bind(&SprintGame::moveLeft,this));
	EngineInterface::connectKeyboardAction(D,boost::bind(&SprintGame::moveRight,this));

	EngineInterface::addParticleEmiter("Glow1","Data/Particles/smoke.lua",boost::bind(&SprintGame::initEngineParticle,
		this,_1),boost::bind(&SprintGame::updateEngineParticle,this,_1,_2),Vector3D());
	EngineInterface::addParticleEmiter("Glow2","Data/Particles/smoke.lua",boost::bind(&SprintGame::initEngineParticle2,
		this,_1),boost::bind(&SprintGame::updateEngineParticle2,this,_1,_2),Vector3D());
	EngineInterface::addParticleEmiter("Glow3","Data/Particles/smoke.lua",boost::bind(&SprintGame::initEngineParticle3,
		this,_1),boost::bind(&SprintGame::updateEngineParticle3,this,_1,_2),Vector3D());
	EngineInterface::addParticleEmiter("Glow4","Data/Particles/smoke.lua",boost::bind(&SprintGame::initEngineParticle4,
		this,_1),boost::bind(&SprintGame::updateEngineParticle4,this,_1,_2),Vector3D());

	EngineInterface::playMusicTrack("Track");
	EngineInterface::initializeFont("Font",32);
	EngineInterface::addSprite("AyumiLogo",Vector3D(-500.0f,-340.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));
	EngineInterface::addText("Score",lexical_cast<string>(score),Vector3D(0.0f,550.0f,0.0f));
	EngineInterface::addText("Time","Time " ,Vector3D(-200.0f,550.0f,0.0f));
	EngineInterface::addText("Lifes","Lifes: ",Vector3D(-700.0f,550.0f,0.0f));
	EngineInterface::addText("Lifes2",lexical_cast<string>(lifeAmount),Vector3D(-500.0f,550.0f,0.0f));

	moveDirection.set(0.0f,0.0f,0.0f);
	disturbance.set(CommonMath::random(-0.2f,0.2f),CommonMath::random(-0.2f,0.2f),CommonMath::random(-0.2f,0.2f));
	resistance.set(0.01f,0.01f,0.01f);
	EngineInterface::updateShadowSource(0,Vector3D(0.0,10.0f,0.0f),Vector3D(90.0f,0.0f,0.0f));
}

void SprintGame::gameState()
{
	EngineInterface::runGameLoop(&isRunning);
}

void SprintGame::exitGame()
{
	isRunning = false;
	gameOver = true;
}

void SprintGame::collisionCallback()
{
	string name1 = EngineInterface::getCollisionActors().first;
	string name2 = EngineInterface::getCollisionActors().second;

	if(name1 != "Vehicle")
		EngineInterface::getEntity(name1)->entityPhysics.acceleration[2] = -2000.0f;
	else if(name2 != "Vehicle")
		EngineInterface::getEntity(name2)->entityPhysics.acceleration[2] = -2000.0f;
	
	lifeAmount--;
	if(lifeAmount == 0)
	{
		isRunning = false;
		gameOver = true;
	}

    ostringstream ss;
    ss << lifeAmount;
	EngineInterface::updateText("Lifes2",ss.str());
}

void SprintGame::initGameOverState()
{
	EngineInterface::stopMusicTrack("Track");
	EngineInterface::deleteGameLoopTask("ScoreUpdate");
	EngineInterface::connectKeyboardAction(Escape,boost::bind(&SprintGame::exitGame,this));
	isRunning = true;
	EngineInterface::clearRenderQueue();
	EngineInterface::clearScene();
	EngineInterface::updateEffects("Data/SprintGame/effectLoad.lua");
	EngineInterface::addRenderTask("renderSprites");	
	EngineInterface::deleteText("Time");
	EngineInterface::deleteText("Score");
	EngineInterface::deleteText("Lifes");
	EngineInterface::deleteText("Lifes2");
	EngineInterface::addText("GameOver","GameOver!",Vector3D(-100.0f,0.0f,0.0f));

	if(!gameOver)
	{
		EngineInterface::addText("Win","You Win!",Vector3D(-250.0f,-50.0f,0.0f));
		EngineInterface::addText("Score","Your score is: ",Vector3D(-250.0f,-100.0f,0.0f));
	    ostringstream ss;
		ss << fixed << setprecision(2) << score;
		string finalScore = ss.str();
		EngineInterface::addText("Result",finalScore,Vector3D(-100.0f,-150.0f,0.0f));
	}
	else
		EngineInterface::addText("Loose","You Loose! Try again.",Vector3D(-250.0f,-50.0f,0.0f));
}

void SprintGame::gameOverState()
{
	EngineInterface::runGameLoop(&isRunning,false);
}

void SprintGame::moveLeft()
{
	moveDirection[0] = -1.0f;
	vehicle->entityPhysics.velocity[0] += acceleration[0] * EngineInterface::getElapsedTime();
}

void SprintGame::moveRight()
{
	moveDirection[0] = 1.0f;
	vehicle->entityPhysics.velocity[0] += acceleration[0] * EngineInterface::getElapsedTime();
}

void SprintGame::accelerate()
{
	moveDirection[2] = -1.0f;
	vehicle->entityPhysics.velocity[2] += acceleration[2] * EngineInterface::getElapsedTime();
}

void SprintGame::updateVehicle(SceneEntity* entity, const float elapsedTime)
{
	Vector3D position = entity->entityState.position;

	if(position[2] < -500.0f) //finish line
	{
		isRunning = false;
		gameOver = false;
		return;
	}
	
	Vector3D cameraPosition = camera->getPosition();
	disturbance.set(CommonMath::random(-0.2f,0.2f),CommonMath::random(-0.2f,0.2f),CommonMath::random(-0.2f,0.2f));
	
	if(entity->entityPhysics.velocity[2] > 0.0f)
	{
		position[2] += moveDirection[2]*(entity->entityPhysics.velocity[2]*elapsedTime + (acceleration[2]*acceleration[2]*elapsedTime*0.5f));
		entity->entityPhysics.velocity[2] -= resistance[2]*elapsedTime;
	}
	if(entity->entityPhysics.velocity[0] > 0.0f)
	{
		position[0] += moveDirection[0]*(entity->entityPhysics.velocity[0]*elapsedTime + (acceleration[0]*acceleration[0]*elapsedTime*0.5f));
		entity->entityPhysics.velocity[0] -= resistance[2]*elapsedTime;		
	}

	position[0] += moveDirection[0]*(entity->entityPhysics.velocity[0]*elapsedTime + (acceleration[0]*acceleration[0]*elapsedTime*0.5f));
	position[2] += moveDirection[2]*(entity->entityPhysics.velocity[2]*elapsedTime + (acceleration[2]*acceleration[2]*elapsedTime*0.5f));
	
	if(position[0] < -3.3f)
		position[0] = -3.3f;
	else if(position[0] > 3.3f)
		position[0] = 3.3f; 

	entity->entityState.position = position;
	camera->setPosition(position[0],position[1]+0.35f,position[2]+1.5f);
}

void SprintGame::updateScore()
{
	score += EngineInterface::getElapsedTime();
    ostringstream ss;
    ss << fixed << setprecision(2) << score;
	EngineInterface::updateText("Score",ss.str());
	Vector3D position = vehicle->entityState.position;
	position += Vector3D(0.0f,5.0f,0.0f);
	EngineInterface::updateShadowSource(0,position,Vector3D(90.0f,0.0f,0.0f));
}

void SprintGame::initEngineParticle(ParticleEmiter* emiter)
{
	emiter->origin = vehicle->entityState.position;
	emiter->origin += Vector3D(-0.16f,-0.03f,0.13f);
}
void SprintGame::updateEngineParticle(ParticleEmiter* emiter, const float elapsedTime)
{
	emiter->origin = vehicle->entityState.position;
	emiter->origin += Vector3D(-0.16f,-0.03f,0.13f);
	for(int i = 0; i < emiter->particleAmount; i++)
	{
		emiter->particles[i].lifeTime -= elapsedTime;
		if(emiter->particles[i].lifeTime < 0.0f)
		{
			emiter->particles[i].lifeTime = 1.0f;
			emiter->particles[i].position[0] = 0.0f;
			emiter->particles[i].position[1] = 0.0f;
			emiter->particles[i].position[2] = 0.0f;
			emiter->particles[i].color[3] = 0.0f;
			emiter->particles[i].velocity[2] = 0.0f;

			emiter->particles[i].velocity[0] = CommonMath::random(-0.01f,0.01f);
			emiter->particles[i].velocity[1] = CommonMath::random(-0.01f,0.01f);
			emiter->particles[i].velocity[2] = CommonMath::random(0.0f,0.06f);
		}
		else
		{
			emiter->particles[i].color[3] += elapsedTime/5;
			emiter->particles[i].position[0] += emiter->particles[i].velocity[0] * elapsedTime;
			emiter->particles[i].position[1] += emiter->particles[i].velocity[1] * elapsedTime;
			emiter->particles[i].position[2] += emiter->particles[i].velocity[2] * elapsedTime;
		}
		emiter->points[i].x = emiter->particles[i].position[0];
		emiter->points[i].y = emiter->particles[i].position[1];
		emiter->points[i].z = emiter->particles[i].position[2];
	}
}

void SprintGame::initEngineParticle2(ParticleEmiter* emiter)
{
	emiter->origin = vehicle->entityState.position;
	emiter->origin += Vector3D(-0.10f,-0.03f,0.13f);
}
void SprintGame::updateEngineParticle2(ParticleEmiter* emiter, const float elapsedTime)
{
	emiter->origin = vehicle->entityState.position;
	emiter->origin += Vector3D(-0.10f,-0.03f,0.13f);
	for(int i = 0; i < emiter->particleAmount; i++)
	{
		emiter->particles[i].lifeTime -= elapsedTime;
		if(emiter->particles[i].lifeTime < 0.0f)
		{
			emiter->particles[i].lifeTime = 1.0f;
			emiter->particles[i].position[0] = 0.0f;
			emiter->particles[i].position[1] = 0.0f;
			emiter->particles[i].position[2] = 0.0f;
			emiter->particles[i].color[3] = 0.0f;
			emiter->particles[i].velocity[2] = 0.0f;

			emiter->particles[i].velocity[0] = CommonMath::random(-0.01f,0.01f);
			emiter->particles[i].velocity[1] = CommonMath::random(-0.01f,0.01f);
			emiter->particles[i].velocity[2] = CommonMath::random(0.0f,0.06f);
		}
		else
		{
			emiter->particles[i].color[3] += elapsedTime/5;
			emiter->particles[i].position[0] += emiter->particles[i].velocity[0] * elapsedTime;
			emiter->particles[i].position[1] += emiter->particles[i].velocity[1] * elapsedTime;
			emiter->particles[i].position[2] += emiter->particles[i].velocity[2] * elapsedTime;
		}
		emiter->points[i].x = emiter->particles[i].position[0];
		emiter->points[i].y = emiter->particles[i].position[1];
		emiter->points[i].z = emiter->particles[i].position[2];
	}
}

void SprintGame::initEngineParticle3(ParticleEmiter* emiter)
{
	emiter->origin = vehicle->entityState.position;
	emiter->origin += Vector3D(0.10f,-0.03f,0.13f);
}
void SprintGame::updateEngineParticle3(ParticleEmiter* emiter, const float elapsedTime)
{
	emiter->origin = vehicle->entityState.position;
	emiter->origin += Vector3D(0.10f,-0.03f,0.13f);
	for(int i = 0; i < emiter->particleAmount; i++)
	{
		emiter->particles[i].lifeTime -= elapsedTime;
		if(emiter->particles[i].lifeTime < 0.0f)
		{
			emiter->particles[i].lifeTime = 1.0f;
			emiter->particles[i].position[0] = 0.0f;
			emiter->particles[i].position[1] = 0.0f;
			emiter->particles[i].position[2] = 0.0f;
			emiter->particles[i].color[3] = 0.0f;
			emiter->particles[i].velocity[2] = 0.0f;

			emiter->particles[i].velocity[0] = CommonMath::random(-0.01f,0.01f);
			emiter->particles[i].velocity[1] = CommonMath::random(-0.01f,0.01f);
			emiter->particles[i].velocity[2] = CommonMath::random(0.0f,0.06f);
		}
		else
		{
			emiter->particles[i].color[3] += elapsedTime/5;
			emiter->particles[i].position[0] += emiter->particles[i].velocity[0] * elapsedTime;
			emiter->particles[i].position[1] += emiter->particles[i].velocity[1] * elapsedTime;
			emiter->particles[i].position[2] += emiter->particles[i].velocity[2] * elapsedTime;
		}
		emiter->points[i].x = emiter->particles[i].position[0];
		emiter->points[i].y = emiter->particles[i].position[1];
		emiter->points[i].z = emiter->particles[i].position[2];
	}
}

void SprintGame::initEngineParticle4(ParticleEmiter* emiter)
{
	emiter->origin = vehicle->entityState.position;
	emiter->origin += Vector3D(0.16f,-0.03f,0.13f);
}
void SprintGame::updateEngineParticle4(ParticleEmiter* emiter, const float elapsedTime)
{
	emiter->origin = vehicle->entityState.position;
	emiter->origin += Vector3D(0.16f,-0.03f,0.13f);
	for(int i = 0; i < emiter->particleAmount; i++)
	{
		emiter->particles[i].lifeTime -= elapsedTime;
		if(emiter->particles[i].lifeTime < 0.0f)
		{
			emiter->particles[i].lifeTime = 1.0f;
			emiter->particles[i].position[0] = 0.0f;
			emiter->particles[i].position[1] = 0.0f;
			emiter->particles[i].position[2] = 0.0f;
			emiter->particles[i].color[3] = 0.0f;
			emiter->particles[i].velocity[2] = 0.0f;

			emiter->particles[i].velocity[0] = CommonMath::random(-0.01f,0.01f);
			emiter->particles[i].velocity[1] = CommonMath::random(-0.01f,0.01f);
			emiter->particles[i].velocity[2] = CommonMath::random(0.0f,0.06f);
		}
		else
		{
			emiter->particles[i].color[3] += elapsedTime/5;
			emiter->particles[i].position[0] += emiter->particles[i].velocity[0] * elapsedTime;
			emiter->particles[i].position[1] += emiter->particles[i].velocity[1] * elapsedTime;
			emiter->particles[i].position[2] += emiter->particles[i].velocity[2] * elapsedTime;
		}
		emiter->points[i].x = emiter->particles[i].position[0];
		emiter->points[i].y = emiter->particles[i].position[1];
		emiter->points[i].z = emiter->particles[i].position[2];
	}
}