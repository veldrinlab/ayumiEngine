/**
 * File contains declaration of EntityPhysics structure.
 * @file    EntityPhysics.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-10
 */

#ifndef ENTITYPHYSICS_HPP
#define ENTITYPHYSICS_HPP

#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Structure represents SceneEntity physics data like velocity and mass which will
		 * be used physics calculation.
		 */
		struct EntityPhysics
		{
			AyumiMath::Vector3D velocity;
			AyumiMath::Vector3D acceleration;
			float entityMass;
			bool isKinematic;
		};
	}
}
#endif
