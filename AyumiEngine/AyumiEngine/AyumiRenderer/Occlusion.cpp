/**
 * File contains definition of Occlusion class.
 * @file	Occlusion.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-09-05
 */

#include "Occlusion.hpp"

using namespace std;
using namespace AyumiEngine::AyumiScene;

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class default constructor. Nothing to do.
		 */
		Occlusion::Occlusion()
		{
			queryCounter = 0;
		}

		/**
		 * Class destructor, free allocated memory. Delete queries.
		 */
		Occlusion::~Occlusion()
		{
			for(unsigned i = 0; i < queries.size(); i++)
				glDeleteQueries(1,&queries[i]);
			queries.clear();
		}

		/**
		 * Function is used to sort entities in z-order.
		 */
		bool sortEntities(SceneEntity* a, SceneEntity* b)
		{
			return (a->entityState.position.z() > b->entityState.position.z());
		}

		/**
		 * Function is used to sort entities in z-order.
		 */
		bool sortEntities2(SceneEntity* a, SceneEntity* b)
		{
			return (a->entityState.position.z() < b->entityState.position.z());
		}

		/**
		 * Method is used to prepare engine scene entities - sort in in z-order to perform occlusion query.
		 * @param	engineScene is pointer to engine scene.
		 */
		void Occlusion::prepareEntities(SceneManager* engineScene)
		{
			vector<SceneEntity*>* entities = &engineScene->getSceneGraph()->sceneEntities;
			Camera* camera = engineScene->getWorldCamera();

			if(camera->getViewDirection().z() < 0)
				sort(entities->begin(),entities->end(),sortEntities2);
			else
				sort(entities->begin(),entities->end(),sortEntities);
		}

		/**
		 * Method is used to check occlusion query results. Wait for result and if result is 0, set entity state
		 * to invisible.
		 * @param	engineScene is pointer to engine scene.
		 */
		void Occlusion::checkQueriesResults(SceneManager* engineScene)
		{
			vector<SceneEntity*>* entities = &engineScene->getSceneGraph()->sceneEntities;

			for(unsigned int i = 0; i < entities->size(); ++i)
			{
				GLint available;
				do
				{
					glGetQueryObjectiv(queries[i],GL_QUERY_RESULT_AVAILABLE,&available);
				}
				while(!available);
			}

			for(unsigned int i = 0; i < entities->size(); ++i)
			{
				GLint result = 0;
				glGetQueryObjectiv(queries[i],GL_QUERY_RESULT,&result);
     
				if(result == 0)
					entities->at(i)->entityState.isVisible = false;
			}
		}
	
		/**
		 * Method is used to add new query - one non-independent scene entity needs one query object. Engine call
		 * this method when prepareEntity is called.
		 */
		void Occlusion::addNewQuery()
		{
			GLuint query;
			glGenQueries(1,&query);
			queries.push_back(query);
		}
		
		/**
		 * Method is used to delete query - one non-independent scene entity needs one query object. Engine call this
		 * method when deleting entity from engine scene.
		 */
		void Occlusion::deleteQuery()
		{
			GLuint query;
			query = queries.back();
			glDeleteQueries(1,&query);
			queries.pop_back();
		}

		/**
		 * Accessor to private vailable query from queries collection.
		 * @return	pointer to current qvailable query.
		 */
		GLuint* Occlusion::getQuery()
		{
			int temp = queryCounter;
			queryCounter++;
			if(queryCounter == queries.size())
				queryCounter = 0;
			return &queries[temp];
		}
	}
}
