/**
 * File contains declaration of SceneGraph structure.
 * @file	SceneGraph.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-09
 */

#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include <vector>

#include "SceneEntity.hpp"
#include "AnimatedEntity.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Struture represents engine scene graph which is defined by trees of SceneEntity objects.
		 * Base structure of AyumiEngine SceneGraph is set of lists: one for static entities, independent entities which
		 * is forbidden for culling and animated entities. Each SceneEntity extends SceneNode so user can create
		 * tree representation of scene.
		 */
		struct SceneGraph
		{
			std::vector<SceneEntity*> sceneEntities;
			std::vector<SceneEntity*> independentEntities;
			std::vector<AnimatedEntity*> animatedEntities;
		};
	}
}
#endif
