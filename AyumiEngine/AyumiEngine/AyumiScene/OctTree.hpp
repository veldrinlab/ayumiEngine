/**
 * File contains declaration of OctTree class.
 * @file	OctTree.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-09
 */

#ifndef OCTTREE_HPP
#define OCTTREE_HPP

#include <vector>

#include "SceneEntity.hpp"
#include "../AyumiUtils/BoundingBox.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Enumeration represents all available condition on which we end dividing OctTree to another nodes. 
		 */
		enum DivideCondition
		{
			MAXDEPTH,
			NODESIZE,
			MINENTITY
		};

		/**
		 * Structure represents OctTree Node which store data about Bounding Volume, position and entities.
		 */
		struct OctNode
		{
			OctNode* parent;
			OctNode* children[8];
			AyumiUtils::BoundingBox volume;
			AyumiMath::Vector3D position;
			AyumiMath::Vector3D size;
			std::vector<SceneEntity*> entities;
		};

		/**
		 * Class represents OctTree data structure which is used in space partitioning. It is simple tree
		 * structure which will improve Frustum Culling operation.
		 */
		class OctTree
		{
		private:
			OctNode* root;
			DivideCondition condition;
			std::vector<SceneEntity*>* sceneEntities;

			void buildRootNode();
			void buildNode(OctNode* parent);
			void createNodeChildren(OctNode* parent, AyumiMath::Vector3D position, const int childID);
			void destroyNode(OctNode* node);
		public:
			OctTree(std::vector<SceneEntity*>* sceneEntities, DivideCondition condition);
			~OctTree();

			void buildOctTree();
			void destroyOctTree();
			
			OctNode* getRoot() const;
		};
	}
}
#endif
