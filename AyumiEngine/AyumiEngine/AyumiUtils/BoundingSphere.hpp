/**
 * File contains declaraion of BoundingSpehre class.
 * @file    BoundingSphere.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-05
 */

#ifndef BOUNDINGSPHERE_HPP
#define BOUNDINGSPHERE_HPP

#include "../AyumiMath/CommonMath.hpp"
#include "../AyumiResource/Mesh.hpp"

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class represents one of engine bounding volumes - bounding sphere. It is used
		 * to create AABB data based on SceneEntity geometry. Bounding sphere structure
		 * will be used in collision detection, scene organization and culling operations.
		 */
		class BoundingSphere
		{
		public:
			AyumiEngine::AyumiMath::Vector3D position;
			float sphereRadius;

			BoundingSphere();
			BoundingSphere(const AyumiResource::Mesh& entityMesh, const AyumiEngine::AyumiMath::Vector3D& center);
			BoundingSphere(const BoundingSphere& boundingVolume);
			~BoundingSphere();
		};
	}
}
#endif
