/**
 * File contains declaration of SceneManager class.
 * @file	SceneManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-09
 */

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <deque>
#include <boost/function.hpp>
#include <string>

#include "SceneGraph.hpp"
#include "OctTree.hpp"
#include "Frustum.hpp"
#include "StaticCamera.hpp"
#include "FirstPersonCamera.hpp"
#include "FreeCamera.hpp"
#include "FlightCamera.hpp"
#include "ThirdPersonCamera.hpp"

//#include <tbb/task_scheduler_init.h>
//#include <tbb/parallel_for.h>
//#include <tbb/blocked_range.h>

namespace AyumiEngine
{
	namespace AyumiScene
	{
		typedef std::pair<std::string, boost::function<void()>> UpdateTask;
		typedef std::deque<UpdateTask> UpdateQueue;

		/**
		 * Class represents one of main Engine modules which is used to store and update 2D/3D scene objects.
		 * SceneManager store entities in SceneGraph and use such techniques as OctTree and Frustum culling to 
		 * entities visiblity tests and update them. Each entity can be updated in three possible way: extending,
		 * functor and Lua script. Renderer use SceneManager to render visible entities. Pipeline is done by
		 * task queue.
		 */
		class SceneManager
		{
		private:
			UpdateQueue updateQueue;
			SceneGraph* sceneGraph;
			OctTree* octTree;
			Camera* sceneCamera;
			Frustum* frustumCulling;
			float deltaTime;
			double accum;
			int counter;

			//WGK tests
			UpdateQueue preUpdateQueue;
			UpdateQueue parallelUpdateQueue;
			UpdateQueue postUpdateQueue;

			void rebuildOctTree();
			void performFrustumCulling();
			void performTreeFrustumCulling();
			void performNodeFrustumCulling(OctNode* node);
			void updateEntities();
			void prepareEntityVirtualMachine(SceneEntity* entity);
			
		public:
			SceneManager();
			~SceneManager();

			void initializeSceneManager();
			void updateScene(const float elapsedTime);
			void addUpdateTask(const std::string& task);
			void addCustomUpdateTask(const std::string& task, boost::function<void()> function);
			void deleteUpdateTask(const std::string& task);
			void addSceneEntity(SceneEntity* entity);			
			void addIndependentEntity(SceneEntity* entity);
			void addAnimatedEntity(AnimatedEntity* entity);

			void deleteSceneEntity(const std::string& name);
			void deleteIndependentEntity(const std::string& name);
			void deleteAnimatedEntity(const std::string& name);
			void clearScene();

			void addCamera(Camera* sceneCamera);

			SceneGraph* getSceneGraph() const;
			Camera* getWorldCamera() const;
			OctTree* getOctTree() const;
			float getDeltaTime() const;

			SceneEntity* getEntity(const std::string& name);
			AnimatedEntity* getAnimatedEntity(const std::string& name);
		};
	}
}
#endif
