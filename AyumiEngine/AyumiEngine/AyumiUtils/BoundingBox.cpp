/**
 * File contains definition of BoundingBox class.
 * @file    BoundingBox.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#include "BoundingBox.hpp"

using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class default constructor. Set object member default values.
		 */
		BoundingBox::BoundingBox()
		{
			min = Vector3D(0.0f,0.0f,0.0f);
			max = Vector3D(0.0f,0.0f,0.0f);
		}

		/**
		 * Class constructor with initialize parameters.
		 * @param	entityMesh is scene entity geometry data.
		 */
		BoundingBox::BoundingBox(const Mesh& entityMesh)
		{
			min = Vector3D(100000.0f,100000.0f,100000.0f);
			max = Vector3D(-100000.0f,-100000.0f,-100000.0f);

			Vertex<>* verts = entityMesh.getVertices();

			for(int i = 0; i < entityMesh.getVerticesAmount(); ++i)
			{
				if(min[0] >= verts[i].x) min[0] = verts[i].x;
				if(min[1] >= verts[i].y) min[1] = verts[i].y;
				if(min[2] >= verts[i].z) min[2] = verts[i].z;

				if(max[0] <= verts[i].x) max[0] = verts[i].x;
				if(max[1] <= verts[i].y) max[1] = verts[i].y;
				if(max[2] <= verts[i].z) max[2] = verts[i].z;
			}
		}

		/**
		 * Class copy constructor.
		 * @param	boundingVolume is copy source object.
		 */
		BoundingBox::BoundingBox(const BoundingBox& boundingVolume)
		{
			this->min = boundingVolume.min;
			this->max = boundingVolume.max;
		}

		/**
		 * Class destructor, free allocated memory. In this case, nothing to delete.
		 */
		BoundingBox::~BoundingBox()
		{

		}
	}
}
