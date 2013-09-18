/**
 * File contains declaration of EntityGeometry structure.
 * @file    EntityGeometry.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-10
 */

#ifndef ENTITYGEOMETRY_HPP
#define ENTITYGEOMETRY_HPP

#include "../AyumiResource/Mesh.hpp"
#include "../AyumiUtils/VertexArrayObject.hpp"
#include "../AyumiUtils/VertexBufferObject.hpp"
#include "../AyumiUtils/BoundingBox.hpp"
#include "../AyumiUtils/BoundingSphere.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Structure represents SceneEntity geometry data: Vertex Buffers, Mesh data
		 * and bounding volumes, which will be used in geometry rendering.
		 */
		struct EntityGeometry
		{
			AyumiResource::Mesh* geometryMesh;
			AyumiUtils::VertexArrayObject* geometryVao;
			AyumiUtils::VertexBufferObject* geomteryVbo;
			AyumiUtils::BoundingBox* geometryBox;
			AyumiUtils::BoundingSphere* geometrySphere;
		};
	}
}
#endif
