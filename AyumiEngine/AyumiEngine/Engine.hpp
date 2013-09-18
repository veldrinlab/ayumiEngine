/**
 * File contains declaraion of Engine class.
 * @file    Engine.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-12
 */

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <boost/thread.hpp>

#include "AyumiCore/ContextManager.hpp"
#include "AyumiCore/Timer.hpp"
#include "AyumiRenderer/Renderer.hpp"
#include "AyumiScene/SceneManager.hpp"
#include "AyumiInput/InputManager.hpp"
#include "AyumiSound/SoundManager.hpp"
#include "AyumiPhysics/PhysicsManager.hpp"

namespace AyumiEngine
{
	typedef std::pair<std::string, boost::function<void()>> EngineTask;
	typedef std::deque<EngineTask> EngineQueue;

	/**
	 * Class represents AyumiEngine main part - Engine itself. It store all engine modules
	 * managers like Renderer or Context, initialize them and clean at application end.
	 */
	class Engine
	{
	private:
		EngineQueue mainQueue;
		boost::mutex lock;
		boost::thread physicsThread;
		bool isPhysicsThreadAlive;
		AyumiCore::ContextManager* engineContext;
		AyumiCore::Timer* engineMainTimer;
		AyumiCore::Timer* enginePhysicsTimer;
		AyumiRenderer::Renderer* engineRenderer;
		AyumiScene::SceneManager* engineScene;
		AyumiInput::InputManager* engineInput;
		AyumiSound::SoundManager* engineSound;
		AyumiPhysics::PhysicsManager* enginePhysics;
	
		void mainThreadLoop();
		void physicsThreadLoop();

	public:
		Engine();
		~Engine();

		void initializeEngine(const bool physicsUsage);
		void addTask(const std::string& taskName, boost::function<void()> task);
		void deleteTask(const std::string& taskName);
		void mainThread();
		void runPhysicsThread();
		void killPhysicsThread();

		AyumiCore::ContextManager* getEngineContext() const;
		AyumiRenderer::Renderer* getEngineRenderer() const;
		AyumiScene::SceneManager* getEngineScene() const;
		AyumiInput::InputManager* getEngineInput() const;
		AyumiSound::SoundManager* getEngineSound() const;
		AyumiPhysics::PhysicsManager* getEnginePhysics() const;
		AyumiCore::Timer* getEngineMainTimer() const;
		AyumiCore::Timer* getEnginePhysicsTimer() const;
	};
}
#endif
