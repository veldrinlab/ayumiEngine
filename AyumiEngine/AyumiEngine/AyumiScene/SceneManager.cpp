/**
 * File contains definition of SceneManager class.
 * @file	SceneManager.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-09
 */

#include "SceneManager.hpp"

using namespace std;
using namespace boost;
//using namespace tbb;
using namespace AyumiEngine::AyumiCore;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiUtils;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * WGK test
		 * Apply Logic task class
		 */
		/*class ApplyLogic 
		{
		private:
			std::vector<SceneEntity*>* const my_entities;
			float deltaTime;

		public:
			void operator() (const tbb::blocked_range<size_t>& r) const
			{
				std::vector<SceneEntity*>* e = my_entities;

				for(size_t i=r.begin(); i!=r.end( ); ++i)
				{
					if(e->at(i)->entityLogic.updateType == EXTENDING)
						e->at(i)->updateEntity(deltaTime);
					else if(e->at(i)->entityLogic.updateType == FUNCTION)
						e->at(i)->entityLogic.updateFunction(e->at(i),deltaTime);
					else if(e->at(i)->entityLogic.updateType == SCRIPT)
						e->at(i)->entityLogic.updateScript->executeScript();
				}
			}
			
			ApplyLogic(std::vector<SceneEntity*>* entities, float time) : my_entities(entities), deltaTime(time) {}
		};*/

		/**
		 * Class default constructor. Create scene management modules like SceneGraph, OctTree and Frustum.
		 */
		SceneManager::SceneManager()
		{
			sceneGraph = new SceneGraph();
			frustumCulling = new Frustum();
			octTree = new OctTree(&sceneGraph->sceneEntities,MINENTITY);
			sceneCamera = new StaticCamera();
			deltaTime = 0.0f;

			//task_scheduler_init init;
		}

		/**
		 * Class destructor, free allocated memory. Clear SceneGraph and delete all scene modules.
		 */
		SceneManager::~SceneManager()
		{
			for(vector<AnimatedEntity*>::const_iterator it = sceneGraph->animatedEntities.begin(); it != sceneGraph->animatedEntities.end(); ++it)
			{
				vector<SceneEntity*>::const_iterator it2 = sceneGraph->sceneEntities.begin();
				for(; it2 != sceneGraph->sceneEntities.end(); ++it2)
					if((*it2)->entityName == (*it)->entityName)
						break;
				sceneGraph->sceneEntities.erase(it2);			
				delete (*it);
			}
			for(vector<SceneEntity*>::const_iterator it = sceneGraph->independentEntities.begin(); it != sceneGraph->independentEntities.end(); ++it)
				delete (*it);
			for(vector<SceneEntity*>::const_iterator it = sceneGraph->sceneEntities.begin(); it != sceneGraph->sceneEntities.end(); ++it)
				delete (*it);
			
			sceneGraph->independentEntities.clear();	
			sceneGraph->animatedEntities.clear();
			updateQueue.clear();
			delete sceneGraph;
			delete sceneCamera;
			delete frustumCulling;
			delete octTree;
		}

		/**
		 * Method is used to initialize default task queue.
		 */
		void SceneManager::initializeSceneManager()
		{
			updateQueue.push_back(make_pair("updateEntities",boost::bind(&SceneManager::updateEntities,this)));
		}

		/**
		 * Method is used to update engine scene. SceneManager use update task queue to update pipeline.
		 * @param	elapsedTime is difference betweenn two frame in seconds.
		 */
		void SceneManager::updateScene(const float elapsedTime)
		{
			deltaTime = elapsedTime;

			//pre np. frustum culling
			
		//	sceneCamera->updatePosition(deltaTime); // camera

			//parallel tasks
			
			//Intel TBB - TODO

			//unsigned n = sceneGraph->independentEntities.size();
			//std::vector<SceneEntity*>* my_entities = &sceneGraph->independentEntities;
			//parallel_for(blocked_range<size_t>(0,n), ApplyLogic(my_entities,deltaTime),auto_partitioner());

			//Pure single thread

			//for(vector<SceneEntity*>::const_iterator i = sceneGraph->independentEntities.begin(); i != sceneGraph->independentEntities.end(); ++i)
			//{
			//	if((*i)->entityLogic.updateType == EXTENDING)
			//		(*i)->updateEntity(deltaTime);
			//	else if((*i)->entityLogic.updateType == FUNCTION)
			//		(*i)->entityLogic.updateFunction((*i),deltaTime);
			//	else if((*i)->entityLogic.updateType == SCRIPT)
			//		(*i)->entityLogic.updateScript->executeScript();
			//}

			for(UpdateQueue::const_iterator it = updateQueue.begin(); it != updateQueue.end(); ++it)
				(*it).second();
		}

		/**
		 * Method is used to add new update task to SceneManager update pipeline. Tasks like rebuil OctTree or
		 * perform frustum culling.
		 * @param	task is name of new task.
		 */
		void SceneManager::addUpdateTask(const string& task)
		{
			UpdateQueue::const_iterator it = updateQueue.begin();

			for(; it != updateQueue.end(); ++it)
				if((*it).first == "rebuildOctTree")
					break;

			if(task == "rebuildOctTree")
				updateQueue.push_front(make_pair("rebuildOctTree",boost::bind(&SceneManager::rebuildOctTree,this)));
			else if(task == "performFrustumCulling")
			{
				if(it == updateQueue.end())
					updateQueue.push_front(make_pair("performFrustumCulling",boost::bind(&SceneManager::performFrustumCulling,this)));
				else
					updateQueue.insert(++it,make_pair("performFrustumCulling",boost::bind(&SceneManager::performFrustumCulling,this)));
			}
			else if(task == "performTreeFrustumCulling")
			{
				if(it == updateQueue.end())
					return;
				else
					updateQueue.insert(++it,make_pair("performTreeFrustumCulling",boost::bind(&SceneManager::performTreeFrustumCulling,this)));
			}
		}

		/**
		 * Method is used to add new update task to SceneManager update pipeline.
		 * @param	task is name of new task.
		 * @param	function is functor of new task.
		 */
		void SceneManager::addCustomUpdateTask(const std::string& task, boost::function<void()> function)
		{
			updateQueue.push_back(make_pair(task,function));	
		}

		/**
		 * Method is used to delete task from SceneManager update pipeline. Tasks like rebuil OctTree or
		 * perform frustum culling.
		 * @param	task is name of task to deete.
		 */
		void SceneManager::deleteUpdateTask(const string& task)
		{
			UpdateQueue::const_iterator it = updateQueue.begin();

			for(; it != updateQueue.end(); ++it)
				if((*it).first == task)
					break;
			if(it != updateQueue.end())
				updateQueue.erase(it);
		}

		/**
		 * Method is used to add new scene entity to engine scene.
		 * @param	entity is pointer to new scene entity.
		 */
		void SceneManager::addSceneEntity(SceneEntity* entity)
		{
			sceneGraph->sceneEntities.push_back(entity);
			if(entity->entityLogic.updateType == SCRIPT)
				prepareEntityVirtualMachine(entity);
		}

		/**
		 * Method is used to add new independent scene entity to engine scene.
		 * @param	entity is pointer to new independent scene entity.
		 */
		void SceneManager::addIndependentEntity(SceneEntity* entity)
		{
			sceneGraph->independentEntities.push_back(entity);
			if(entity->entityLogic.updateType == SCRIPT)
				prepareEntityVirtualMachine(entity);
		}

		/**
		 * Method is used to add new animated scene entity to engine scene.
		 * @param	entity is pointer to new animated scene entity.
		 */
		void SceneManager::addAnimatedEntity(AnimatedEntity* entity)
		{
			sceneGraph->animatedEntities.push_back(entity);
			sceneGraph->sceneEntities.push_back(entity);
			if(entity->entityLogic.updateType == SCRIPT)
				prepareEntityVirtualMachine(entity);
		}
		
		/**
		 * Method is used to delete scene entity from engine scene
		 * @param	name is entity name id.
		 */
		void SceneManager::deleteSceneEntity(const string& name)
		{
			vector<SceneEntity*>::const_iterator it = sceneGraph->sceneEntities.begin();
			for(; it != sceneGraph->sceneEntities.end(); ++it)
				if((*it)->entityName == name)
					break;
			
			if(it != sceneGraph->sceneEntities.end())
			{
				sceneGraph->sceneEntities.erase(it);
				delete (*it);
			}
		}

		/**
		 * Method is used to delete independent scene entity from engine scene
		 * @param	name is entity name id.
		 */
		void SceneManager::deleteIndependentEntity(const string& name)
		{
			vector<SceneEntity*>::const_iterator it = sceneGraph->independentEntities.begin();
			for(; it != sceneGraph->independentEntities.end(); ++it)
				if((*it)->entityName == name)
					break;
			
			if(it != sceneGraph->independentEntities.end())
			{
				sceneGraph->independentEntities.erase(it);
				delete (*it);
			}
		}

		/**
		 * Method is used to delete animated scene entity from engine scene
		 * @param	name is entity name id.
		 */
		void SceneManager::deleteAnimatedEntity(const string& name)
		{
			vector<AnimatedEntity*>::const_iterator it = sceneGraph->animatedEntities.begin();
			for(; it != sceneGraph->animatedEntities.end(); ++it)
				if((*it)->entityName == name)
					break;
			
			if(it != sceneGraph->animatedEntities.end())
			{
				sceneGraph->animatedEntities.erase(it);
				delete (*it);
			}
		}

		/**
		 * Method is used to delete all scene entities from virtaul world scene
		 */
		void SceneManager::clearScene()
		{
			sceneGraph->sceneEntities.clear();
			sceneGraph->independentEntities.clear();	
			sceneGraph->animatedEntities.clear();
		}

		/**
		 * Method is used to add new camera to engine scene.
		 * @param	sceneCamera is pointer to new camera.
		 */
		void SceneManager::addCamera(Camera* sceneCamera)
		{
			delete this->sceneCamera;
			this->sceneCamera = sceneCamera;
		}

		/**
		 * Accessor to private scene graph member.
		 * @return	pointer to scene graph.
		 */		
		SceneGraph* SceneManager::getSceneGraph() const
		{
			return sceneGraph;
		}

		/**
		 * Accessor to private scene Camera member.
		 * @return	pointer to scene Camera.
		 */
		Camera* SceneManager::getWorldCamera() const
		{
			return sceneCamera;
		}

		/**
		 * Accessor to private scene OctTree member.
		 * @return	pointer to scene OctTree.
		 */
		OctTree* SceneManager::getOctTree() const
		{
			return octTree;
		}

		/**
		 * Accessor to private scene delta time member.
		 * @return	delta time.
		 */
		float SceneManager::getDeltaTime() const
		{
			return deltaTime;
		}

		/**
		 * Accessor to private scene entity member.
		 * @return	pointer to scene entity by name.
		 */
		SceneEntity*  SceneManager::getEntity(const string& name)
		{
			SceneEntity* entity = nullptr;

			vector<SceneEntity*>::const_iterator it = sceneGraph->sceneEntities.begin();
			for(; it != sceneGraph->sceneEntities.end(); ++it)
				if((*it)->entityName == name)
					break;

			if(it != sceneGraph->sceneEntities.end())
			{
				entity = (*it);
				return entity;
			}

			vector<SceneEntity*>::const_iterator it2 = sceneGraph->independentEntities.begin();
			for(; it2 != sceneGraph->independentEntities.end(); ++it2)
				if((*it2)->entityName == name)
					break;
			
			if(it2 != sceneGraph->independentEntities.end())
			{
				entity = (*it2);
				return entity;
			}
			
			return entity;
		}

		/**
		 * Accessor to private scene entity member.
		 * @return	pointer to scene entity by name.
		 */
		AnimatedEntity* SceneManager::getAnimatedEntity(const string& name)
		{
			AnimatedEntity* entity = nullptr;
			vector<AnimatedEntity*>::const_iterator it = sceneGraph->animatedEntities.begin();
			for(; it != sceneGraph->animatedEntities.end(); ++it)
				if((*it)->entityName == name)
					break;

			if(it != sceneGraph->animatedEntities.end())
				entity = (*it);

			return entity;
		}

		/**
		 *  Private method which is used to rebuild scene OctTree to deal with dynamic scene entities.
		 */
		void SceneManager::rebuildOctTree()
		{
			octTree->destroyOctTree();
			octTree->buildOctTree();
		}

		/**
		 * Private method which is used to perform frustum culling on scene entities to check visibility. It is rendering
		 * optimization because there is no need to render not visibile entities.
		 */
		void SceneManager::performFrustumCulling()
		{
			frustumCulling->calculateFrustum(sceneCamera);

			for(vector<SceneEntity*>::const_iterator i = sceneGraph->sceneEntities.begin(); i != sceneGraph->sceneEntities.end(); ++i)
			{
				(*i)->entityState.isVisible = true;

				BoundingBox* volume = (*i)->entityGeometry.geometryBox;

				const float x = (*i)->entityState.position.x();
				const float y = (*i)->entityState.position.y();
				const float z = (*i)->entityState.position.z();
				const float size = (volume->max.x() - volume->min.x())*(*i)->entityState.scale.x();

				if(frustumCulling->isCubeInFrustum(x,y,z,size) == OUTSIDE)
					(*i)->entityState.isVisible = false;
			}
		}

		/**
		 * Private method which is used to perform frustum culling on scene entities to check visibility. It is rendering
		 * optimization because there is no need to render not visibile entities. This method use also OctTree
		 * to visibility optimization.
		 */
		void SceneManager::performTreeFrustumCulling()
		{
			frustumCulling->calculateFrustum(sceneCamera);
			for(vector<SceneEntity*>::const_iterator i = sceneGraph->sceneEntities.begin(); i != sceneGraph->sceneEntities.end(); ++i)
				(*i)->entityState.isVisible = false;

			performNodeFrustumCulling(octTree->getRoot());
		}

		/**
		 * Private method which is used to perform frustum culling on OctTree node - engine use it recursively to check
		 * whole tree.
		 * @param	node is pointer to current node.
		 */
		void SceneManager::performNodeFrustumCulling(OctNode* node)
		{
			const float x = node->position.x();
			const float y = node->position.y();
			const float z = node->position.z();
			const float size = node->size.x()*0.5f;

			if(frustumCulling->isCubeInFrustum(x,y,z,size) == INSIDE)
			{
				for(unsigned i = 0; i < node->entities.size(); i++)
					node->entities[i]->entityState.isVisible = true;	
				return;
			}
			else if(frustumCulling->isCubeInFrustum(x,y,z,size) == PARTIALLY_INSIDE)
			{
				for(int i = 0; i < 8; ++i)
					if(node->children[i] != nullptr)
						performNodeFrustumCulling(node->children[i]);
			}
			else if(frustumCulling->isCubeInFrustum(x,y,z,size) == OUTSIDE)
			{
				for(unsigned i = 0; i < node->entities.size(); i++)
					node->entities[i]->entityState.isVisible = false;
				return;
			}
		}

		/**
		 * Private method which is used to update engine scene entities.
		 */
		void SceneManager::updateEntities()
		{
			sceneCamera->updatePosition(deltaTime);

			for(vector<SceneEntity*>::const_iterator i = sceneGraph->sceneEntities.begin(); i != sceneGraph->sceneEntities.end(); ++i)
			{
				if((*i)->entityLogic.updateType == EXTENDING)
					(*i)->updateEntity(deltaTime);
				else if((*i)->entityLogic.updateType == FUNCTION)
					(*i)->entityLogic.updateFunction((*i),deltaTime);
				else if((*i)->entityLogic.updateType == SCRIPT)
					(*i)->entityLogic.updateScript->executeScript();
			}

			for(vector<SceneEntity*>::const_iterator i = sceneGraph->independentEntities.begin(); i != sceneGraph->independentEntities.end(); ++i)
			{
				if((*i)->entityLogic.updateType == EXTENDING)
					(*i)->updateEntity(deltaTime);
				else if((*i)->entityLogic.updateType == FUNCTION)
					(*i)->entityLogic.updateFunction((*i),deltaTime);
				else if((*i)->entityLogic.updateType == SCRIPT)
					(*i)->entityLogic.updateScript->executeScript();
			}
			
			for(vector<AnimatedEntity*>::const_iterator i = sceneGraph->animatedEntities.begin(); i != sceneGraph->animatedEntities.end(); ++i)
			{
				(*i)->updateAnimation(deltaTime);

				if((*i)->entityLogic.updateType == EXTENDING)
					(*i)->updateEntity(deltaTime);
				else if((*i)->entityLogic.updateType == FUNCTION)
					(*i)->entityLogic.updateFunction((*i),deltaTime);
				else if((*i)->entityLogic.updateType == SCRIPT)
					(*i)->entityLogic.updateScript->executeScript();	
			}
		}

		/**
		 * Private method which is used to prepare entity virtual machine in order to update script
		 * can access delta time value.
		 */
		void SceneManager::prepareEntityVirtualMachine(SceneEntity* entity)
		{
			luabind::module(entity->entityLogic.virtualMachine)
			[
				luabind::class_<SceneManager>("SceneManager")
				.def("getDeltaTime",&SceneManager::getDeltaTime)
			];

			luabind::globals(entity->entityLogic.virtualMachine)["Scene"] = this;
		}
	}
}
