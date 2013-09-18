/**
 * File contains declaraion of BoundingBox class.
 * @file    BoundingBox.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include "../AyumiMath/CommonMath.hpp"
#include "../AyumiResource/Mesh.hpp"

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class represents one of engine bounding volumes - bounding box. It is used
		 * to create AABB data based on SceneEntity geometry. Bounding box structure
		 * will be used in collision detection, scene organization and culling operations.
		 */
		class BoundingBox
		{
		public:
			AyumiEngine::AyumiMath::Vector3D min;
			AyumiEngine::AyumiMath::Vector3D max;

			BoundingBox();
			BoundingBox(const AyumiResource::Mesh& entityMesh);
			BoundingBox(const BoundingBox& boundingVolume);
			~BoundingBox();
		};
	}
}
#endif
