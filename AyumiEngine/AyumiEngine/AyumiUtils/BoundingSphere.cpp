/**
 * File contains definition of BoundingSpehre class.
 * @file    BoundingSphere.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-05
 */

#include "BoundingSphere.hpp"

using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class default constructor. Set object member default values.
		 */
		BoundingSphere::BoundingSphere()
		{
			this->sphereRadius = 0.0f;
			this->position = Vector3D(0.0f,0.0f,0.0f);
		}
		
		/**
		 * Class constructor with initialize parameters.
		 * @param	entityMesh is scene entity geometry data.
		 * @param	center is bounding sphere center - entity position.
		 */
		BoundingSphere::BoundingSphere(const Mesh& entityMesh, const Vector3D& center)
		{
			position = center;

			float currentDistance = 0.0f;
			float maxDistance = 0.0f;
			Vertex<>* verts = entityMesh.getVertices();
			Vector3D temp;

			for(int i = 0; i < entityMesh.getVerticesAmount(); ++i)
			{
				temp.set(verts[i].x,verts[i].y,verts[i].z);		
				currentDistance = (temp - center).length();

				if(currentDistance > maxDistance)
					maxDistance = currentDistance;
			}

			sphereRadius = sqrt(maxDistance);
		}

		/**
		 * Class copy constructor.
		 * @param	boundingVolume is copy source object.
		 */
		BoundingSphere::BoundingSphere(const BoundingSphere& boundingVolume)
		{
			this->position = boundingVolume.position;
			this->sphereRadius = boundingVolume.sphereRadius;
		}

		/**
		 * Class destructor, free allocated memory. In this case, nothing to delete.
		 */
		BoundingSphere::~BoundingSphere()
		{

		}
	}
}
