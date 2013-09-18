/**
 * File contains declaration of Occlusion class.
 * @file	Occlusion.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-09-05
 */

#ifndef OCCLUSION_HPP
#define OCCLUSION_HPP

#include <GL/glew.h>
#include <vector>

#include "../AyumiScene/SceneManager.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class represents OpenGL 3.3 API Occlusion Query functionality adapter. We use it to store queries
		 * collection, add/delete new query and run occlusion culling which is used to check if entity is visible.
		 * It is one off typical scene culling methods which check if entity is occluded by another one.
		 */
		class Occlusion
		{
		private:
			std::vector<GLuint> queries;
			int queryCounter;
		public:
			Occlusion();
			~Occlusion();

			void prepareEntities(AyumiScene::SceneManager* engineScene);
			void checkQueriesResults(AyumiScene::SceneManager* engineScene);			
			void addNewQuery();
			void deleteQuery();
			GLuint* getQuery();
		};
	}
}
#endif
