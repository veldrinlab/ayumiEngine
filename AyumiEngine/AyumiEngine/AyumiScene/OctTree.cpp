/**
 * File contains definition of OctTree class.
 * @file	OctTree.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-09
 */

#include "OctTree.hpp"

using namespace std;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class constructor with initialize parameters.
		 * @param	sceneEntities is collection of scene entities pointers.
		 * @param	condition is enumeration that describes when we must stop building OctTree.
		 */
		OctTree::OctTree(vector<SceneEntity*>* sceneEntities, DivideCondition condition)
		{
			root = nullptr;
			this->sceneEntities = sceneEntities;
			this->condition = condition;
		}

		/**
		 * Class destructor, free allocated memeory. Destroy whole tree nodes.
		 */
		OctTree::~OctTree()
		{
			destroyOctTree();
		}

		/**
		 * Private method which is used to create tree root by search min and max vectors of whole scene bounding box.
		 */
		void OctTree::buildRootNode()
		{
			OctNode* rootNode = new OctNode();

			rootNode->parent = nullptr;
			for(int i = 0; i < 8; ++i)
				rootNode->children[i] = nullptr;

			rootNode->volume.min = Vector3D(10000000.0f,10000000.0f,10000000.0f);
			rootNode->volume.max = Vector3D(-10000000.0f,-10000000.0f,-10000000.0f);

			for(unsigned i = 0; i < sceneEntities->size(); i++)
			{ 
				float xMax = sceneEntities->at(i)->entityGeometry.geometryBox->max[0] + sceneEntities->at(i)->entityState.position[0];
				float yMax = sceneEntities->at(i)->entityGeometry.geometryBox->max[1] + sceneEntities->at(i)->entityState.position[1];
				float zMax = sceneEntities->at(i)->entityGeometry.geometryBox->max[2] + sceneEntities->at(i)->entityState.position[2];

				float xMin = sceneEntities->at(i)->entityGeometry.geometryBox->min[0] + sceneEntities->at(i)->entityState.position[0];
				float yMin = sceneEntities->at(i)->entityGeometry.geometryBox->min[1] + sceneEntities->at(i)->entityState.position[1];
				float zMin = sceneEntities->at(i)->entityGeometry.geometryBox->min[2] + sceneEntities->at(i)->entityState.position[2];

				if(rootNode->volume.max[0] <= xMax)
					rootNode->volume.max[0] = xMax;
				if(rootNode->volume.max[1] <= yMax)
					rootNode->volume.max[1] = yMax;
				if(rootNode->volume.max[2] <= zMax)
					rootNode->volume.max[2] = zMax;

				if(rootNode->volume.min[0] >= xMin)
					rootNode->volume.min[0] = xMin;
				if(rootNode->volume.min[1] >= yMin)
					rootNode->volume.min[1] = yMin;
				if(rootNode->volume.min[2] >= zMin)
					rootNode->volume.min[2] = zMin;
			}

			rootNode->position.setX(rootNode->volume.max.x() - ((rootNode->volume.max.x() - rootNode->volume.min.x())/2.0f));
			rootNode->position.setY(rootNode->volume.max.y() - ((rootNode->volume.max.y() - rootNode->volume.min.y())/2.0f));
			rootNode->position.setZ(rootNode->volume.max.z() - ((rootNode->volume.max.z() - rootNode->volume.min.z())/2.0f));
			
			rootNode->size.setX((rootNode->volume.max.x() - rootNode->volume.min.x())*0.5f);
			rootNode->size.setY((rootNode->volume.max.y() - rootNode->volume.min.y())*0.5f);
			rootNode->size.setZ((rootNode->volume.max.z() - rootNode->volume.min.z())*0.5f);

			rootNode->entities = *sceneEntities;
			root = rootNode;
		}

		/**
		 * Private method which is used to recursivly build OctTree nodes starting from root.
		 * @param	parent is pointer to new node parent.
		 */
		void OctTree::buildNode(OctNode* parent)
		{
			if(condition == MINENTITY && parent->entities.size() > 1)
			{
				Vector3D position;
				position.set(parent->position.x()+parent->size.x()*0.5f,parent->position.y()+parent->size.y()*0.5f,parent->position.z()+parent->size.z()*0.5f);
				createNodeChildren(parent,position,0);
				buildNode(parent->children[0]);

				position.set(parent->position.x()-parent->size.x()*0.5f,parent->position.y()-parent->size.y()*0.5f,parent->position.z()-parent->size.z()*0.5f);
				createNodeChildren(parent,position,1);
				buildNode(parent->children[1]);

				position.set(parent->position.x()+parent->size.x()*0.5f,parent->position.y()+parent->size.y()*0.5f,parent->position.z()-parent->size.z()*0.5f);
				createNodeChildren(parent,position,2);
				buildNode(parent->children[2]);

				position.set(parent->position.x()+parent->size.x()*0.5f,parent->position.y()-parent->size.y()*0.5f,parent->position.z()+parent->size.z()*0.5f);
				createNodeChildren(parent,position,3);
				buildNode(parent->children[3]);

				position.set(parent->position.x()-parent->size.x()*0.5f,parent->position.y()+parent->size.y()*0.5f,parent->position.z()+parent->size.z()*0.5f);
				createNodeChildren(parent,position,4);
				buildNode(parent->children[4]);

				position.set(parent->position.x()-parent->size.x()*0.5f,parent->position.y()-parent->size.y()*0.5f,parent->position.z()+parent->size.z()*0.5f);
				createNodeChildren(parent,position,5);
				buildNode(parent->children[5]);

				position.set(parent->position.x()+parent->size.x()*0.5f,parent->position.y()-parent->size.y()*0.5f,parent->position.z()-parent->size.z()*0.5f);
				createNodeChildren(parent,position,6);
				buildNode(parent->children[6]);

				position.set(parent->position.x()-parent->size.x()*0.5f,parent->position.y()+parent->size.y()*0.5f,parent->position.z()-parent->size.z()*0.5f);
				createNodeChildren(parent,position,7);
				buildNode(parent->children[7]);
			}
		}

		/**
		 * Method is used to create node children: one of 8, configure it and set entities collection.
		 * @param	parent is pointer to new node parent.
		 * @param	position is children node position in 3D space.
		 * @pram	childID is children node ID(0-7).
		 */
		void OctTree::createNodeChildren(OctNode* parent, Vector3D position, const int childID)
		{
			OctNode* node = new OctNode();

			node->parent = parent; 
			for(int i = 0; i < 8; ++i)
				node->children[i] = nullptr;

			node->volume.min = Vector3D(parent->volume.min.x()*0.5f,parent->volume.min.y()*0.5f,parent->volume.min.z()*0.5f);
			node->volume.max = Vector3D(parent->volume.max.x()*0.5f,parent->volume.max.y()*0.5f,parent->volume.max.z()*0.5f);
			node->position = position;
			node->size = Vector3D(parent->size.x()*0.5f,parent->size.y()*0.5f,parent->size.z()*0.5f);
			
			for(unsigned i = 0; i < sceneEntities->size(); i++)
			{
				Vector3D entityMin = sceneEntities->at(i)->entityGeometry.geometryBox->min + sceneEntities->at(i)->entityState.position;
				Vector3D entityMax = sceneEntities->at(i)->entityGeometry.geometryBox->max + sceneEntities->at(i)->entityState.position; 
			
				Vector3D nodeMin = node->volume.min + node->position;
				Vector3D nodeMax = node->volume.max + node->position; 

				if( entityMin.x() <= nodeMax.x() && entityMin.x() >= nodeMin.x() &&
					entityMin.y() <= nodeMax.y() && entityMin.y() >= nodeMin.y() &&
					entityMin.z() <= nodeMax.z() && entityMin.z() >= nodeMin.z() &&
					entityMax.x() <= nodeMax.x() && entityMax.x() >= nodeMin.x() &&
					entityMax.y() <= nodeMax.y() && entityMax.y() >= nodeMin.y() &&
					entityMax.z() <= nodeMax.z() && entityMax.z() >= nodeMin.z())
					node->entities.push_back(sceneEntities->at(i));
			}
			parent->children[childID] = node;
		}

		/**
		 * Private method which is used to recursively delete all tree node without tree root.
		 * @param	node is pointer to tree node.
		 */
		void OctTree::destroyNode(OctNode* node)
		{
			for(int i = 0; i < 8; ++i)
			{
				if(node->children[i] != nullptr)
					destroyNode(node->children[i]);
				else
				{
					delete node;
					return;
				}
			}
		}

		/**
		 * Method is used to examine scene and create OctTree.
		 */
		void OctTree::buildOctTree()
		{
			buildRootNode();
			buildNode(root);
		}

		/**
		 * Method is used to recursively delete tree nodes nad root.
		 */
		void OctTree::destroyOctTree()
		{
			if(root != nullptr)
			{
				destroyNode(root);
				delete root;
			}
		}

		/**
		 * Accessor to private tree root member.
		 * @return	pointer to tree root node.
		 */
		OctNode* OctTree::getRoot() const
		{
			return root;
		}
	}
}
