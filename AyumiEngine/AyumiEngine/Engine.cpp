/**
 * File contains definition of Engine class.
 * @file    Engine.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-12
 */

#include "Engine.hpp"

using namespace std;

namespace AyumiEngine
{
	/**
	 * Class default constructor. Create all engine modules and initialize them.
	 */
	Engine::Engine()
	{
		engineContext = new AyumiCore::ContextManager();
		engineContext->initializeContextManager();
		engineScene = new AyumiScene::SceneManager();
		engineScene->initializeSceneManager();
		engineRenderer = new AyumiRenderer::Renderer(engineScene);
		engineRenderer->initializeRenderer();
		engineInput = new AyumiInput::InputManager(engineContext);
		engineInput->initializeInputManager();
		engineSound = new AyumiSound::SoundManager();
		engineSound->initializeSoundManager();
		engineMainTimer = new AyumiCore::Timer();
		enginePhysicsTimer = nullptr;
		isPhysicsThreadAlive = false;
	}

	/**
	 * Class destructor, free allocated memeory. Delete all created modules.
	 */
	Engine::~Engine()
	{		
		mainQueue.clear();
		delete engineInput;
		delete engineRenderer;
		delete engineScene;
		delete engineMainTimer;
		delete enginePhysicsTimer;
		delete engineContext;
		delete engineSound;
		
		if(enginePhysics != nullptr)
			delete enginePhysics;
	}

	/**
	 * Method is used to initialize and configure engine modules.
	 * @param	physicUsage is engine physics usage boolean flag. If true - use physics module.
	 */
	void Engine::initializeEngine(const bool physicsUsage)
	{
		addTask("MainLoop",boost::bind(&Engine::mainThreadLoop,this));
	
		if(physicsUsage)
		{
			enginePhysicsTimer = new AyumiCore::Timer();
			enginePhysics = new AyumiPhysics::PhysicsManager();
			enginePhysics->initializePhysicsManager();
		}
	}

	/**
	 * Method is used to add new task to engine main loop. User can configure it by adding some new functions
	 * like AI, environment update etc.
	 * @param	taskName is new task name id.
	 * @param	task is new task funtor.
	 */
	void Engine::addTask(const string& taskName, boost::function<void()> task)
	{
		mainQueue.push_back(make_pair(taskName,task));
	}

	/**
	 * Method is used to delete task from engine main loop.
	 * @param	taksName is id of task which user like to delete.
	 */
	void Engine::deleteTask(const string& taskName)
	{
		EngineQueue::const_iterator it = mainQueue.begin();
		for(; it != mainQueue.end(); ++it)
			if((*it).first == taskName)
				break;
		if(it != mainQueue.end())
			mainQueue.erase(it);
	}
	
	/**
	 * Method is used to run engine main thread.
	 */
	void Engine::mainThread()
	{
		for(EngineQueue::const_iterator it = mainQueue.begin(); it != mainQueue.end(); ++it)
			(*it).second();
	}

	/**
	 * Method is used to run physics thread.
	 */
	void Engine::runPhysicsThread()
	{
		if(enginePhysics != nullptr && isPhysicsThreadAlive == false)
		{
			isPhysicsThreadAlive = true;
			physicsThread = boost::thread(boost::bind(&Engine::physicsThreadLoop,this));
		}
	}

	/**
	 * Method is used to stop physics thread.
	 */
	void Engine::killPhysicsThread()
	{
		isPhysicsThreadAlive = false;
		physicsThread.join();
	}

	/**
	 * Accessor to private Engine context module.
	 * @return	pointer to Engine context module.
	 */
	AyumiCore::ContextManager* Engine::getEngineContext() const
	{
		return engineContext;
	}

	/**
	 * Accessor to private Engine rendering module.
	 * @return	pointer to Engine rendering module.
	 */
	AyumiRenderer::Renderer* Engine::getEngineRenderer() const
	{
		return engineRenderer;
	}

	/**
	 * Accessor to private Engine scene module.
	 * @return	pointer to Engine scene module.
	 */
	AyumiScene::SceneManager* Engine::getEngineScene() const
	{
		return engineScene;
	}

	/**
	 * Accessor to private Engine input module.
	 * @return	pointer to Engine input module.
	 */
	AyumiInput::InputManager* Engine::getEngineInput() const
	{
		return engineInput;
	}

	/**
	 * Accessor to private Engine sound module.
	 * @return	pointer to Engine sound module.
	 */
	AyumiSound::SoundManager* Engine::getEngineSound() const
	{
		return engineSound;
	}

	/**
	 * Accessor to private Engine physics module.
	 * @return	pointer to Engine physics module.
	 */
	AyumiPhysics::PhysicsManager* Engine::getEnginePhysics() const
	{
		return enginePhysics;
	}

	/**
	 * Accessor to private Engine main timer.
	 * @return	pointer to Engine main timer.
	 */
	AyumiCore::Timer* Engine::getEngineMainTimer() const
	{
		return engineMainTimer;
	}

	/**
	 * Accessor to private Engine physics timer.
	 * @return	pointer to Engine physics timer.
	 */
	AyumiCore::Timer* Engine::getEnginePhysicsTimer() const
	{
		return enginePhysicsTimer;
	}

	/**
	 * Private method which is one of primary engine task. Store fixed time engine loop.
	 */
	void Engine::mainThreadLoop()
	{
		engineMainTimer->updateTimerData();
		while(engineMainTimer->checkTimerAccumulator())
		{
			engineInput->updateInput();
			lock.lock();
			engineScene->updateScene(engineMainTimer->getTimeStep());
			lock.unlock();
			engineMainTimer->eatAccumulatorTime();
		}
			
		engineRenderer->renderScene();
		engineContext->getContextWindow()->display();
	}

	/**
	 * Private method which is one of primary engine task. Store physics fixed time engine loop.
	 * It is used to run in physics thread.
	 */
	void Engine::physicsThreadLoop()
	{
		while(isPhysicsThreadAlive)
		{
			enginePhysicsTimer->updateTimerData();
			while(enginePhysicsTimer->checkTimerAccumulator())
			{
				enginePhysics->updateForce();
				enginePhysics->simulatePhysics(enginePhysicsTimer->getTimeStep()); 
				enginePhysics->getSimulationResults();
				enginePhysicsTimer->eatAccumulatorTime();
			}
			lock.lock();
			enginePhysics->updatePhysics();
			lock.unlock();			
		}
	}
}
