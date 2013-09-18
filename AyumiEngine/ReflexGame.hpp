#ifndef REFLEXGAME_HPP
#define REFLEXGAME_HPP

#include <sstream>
#include <iomanip>

#include "AyumiEngine/EngineInterface.hpp"

class ReflexGame
{
private:
	AyumiEngine::AyumiScene::FirstPersonCamera* camera;
	bool isRunning;
	bool gameOver;
	float score;
	float timeAccumulator;
	float introBlending;
	bool fadeOut;
	int targets;
	bool isFired;;
	int fireAccumulator;

public:
	ReflexGame();
	~ReflexGame();

	void startGame();
	void initIntro();
	void introState();
	void updateIntro();
	void initGame();
	void exitGame();
	void gameState();
	void initGameOverState();
	void gameOverState();

	void updateGun(AyumiEngine::AyumiScene::SceneEntity* entity, const float elapsedTime);
	void updateScore();
	void fire();
};
#endif