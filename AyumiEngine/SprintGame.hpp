#ifndef SPRINTGAME_HPP
#define SPRINTGAME_HPP

#include <sstream>
#include <iomanip>

#include "AyumiEngine/EngineInterface.hpp"

struct Collision
{
	enum Enum
	{
		VEHICLE = (1 << 0),
		BOX = (1 << 1)
	};
};

class SprintGame
{
private:
	AyumiEngine::AyumiScene::FirstPersonCamera* camera;
	AyumiEngine::AyumiScene::SceneEntity* sky;
	AyumiEngine::AyumiScene::SceneEntity* terrain;
	AyumiEngine::AyumiScene::SceneEntity* vehicle;
	std::vector<AyumiEngine::AyumiScene::SceneEntity*> course;

	AyumiEngine::AyumiMath::Vector3D moveDirection;
	AyumiEngine::AyumiMath::Vector3D acceleration;
	AyumiEngine::AyumiMath::Vector3D disturbance;
	AyumiEngine::AyumiMath::Vector3D resistance;
	
	bool isRunning;
	bool gameOver;
	float score;
	float timeAccumulator;
	float introBlending;
	bool fadeOut;
	int lifeAmount;

	//
	float sunTimeAccumulator;
	bool timeUpdate;

	void controlDayTime();
	void updateSunLight();
	void updateONeil(AyumiEngine::AyumiScene::EntityMaterial* material, const float deltaTime);


public:
	SprintGame();
	~SprintGame();

	void startGame();

	void initIntro();
	void introState();
	void updateIntro();

	void initGame();
	void exitGame();
	void gameState();

	void initGameOverState();
	void gameOverState();

	void collisionCallback();

	void moveLeft();
	void moveRight();
	void accelerate();
	void updateVehicle(AyumiEngine::AyumiScene::SceneEntity* entity, const float elapsedTime);
	void updateScore();

	void initEngineParticle(AyumiEngine::AyumiRenderer::ParticleEmiter* emiter);
	void updateEngineParticle(AyumiEngine::AyumiRenderer::ParticleEmiter* emiter, const float elapsedTime);
	void initEngineParticle2(AyumiEngine::AyumiRenderer::ParticleEmiter* emiter);
	void updateEngineParticle2(AyumiEngine::AyumiRenderer::ParticleEmiter* emiter, const float elapsedTime);
	void initEngineParticle3(AyumiEngine::AyumiRenderer::ParticleEmiter* emiter);
	void updateEngineParticle3(AyumiEngine::AyumiRenderer::ParticleEmiter* emiter, const float elapsedTime);
	void initEngineParticle4(AyumiEngine::AyumiRenderer::ParticleEmiter* emiter);
	void updateEngineParticle4(AyumiEngine::AyumiRenderer::ParticleEmiter* emiter, const float elapsedTime);
};
#endif