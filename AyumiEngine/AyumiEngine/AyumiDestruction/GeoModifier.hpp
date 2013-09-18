/**
 * File contains declaraion of GeoModifier class.
 * @file    GeoModifier.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef GEOMODIFIER_HPP
#define GEOMODIFIER_HPP

#include "Object3D.hpp"
#include "Face.hpp"

#include "../AyumiScene/SceneEntity.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		/** 
		 * Class represnets GeoModifier which is used to perform CSG Mesh destruction.
		 */
		class GeoModifier
		{
		private:
			Object3D* firstObject;
			Object3D* secondObject;
	
			Solid* composeSolid(int faceStatus1, int faceStatus2, int faceStatus3);
			void groupObjectComponents(Object3D& object, VertexSet& vertices, IntSet& indices, int faceStatus1, int faceStatus2);
			Solid* convertMeshToSolid(AyumiScene::SceneEntity* mesh);
			AyumiResource::Mesh* convertSolidToMesh(Solid* solid);
		public:
			GeoModifier(AyumiScene::SceneEntity* mesh, AyumiScene::SceneEntity* mesh2);
			virtual ~GeoModifier();

			AyumiResource::Mesh* getDifference();
		};
	}
}
#endif
