/**
 * File contains declaration of EntityState structure.
 * @file    EntityState.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-10
 */

#ifndef ENTITYSTATE_HPP
#define ENTITYSTATE_HPP

#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Structure represents SceneEntity state data like physics parameters and flags,
		 * which will be used in entity update.
		 */
		struct EntityState
		{
			AyumiMath::Vector3D position;
			AyumiMath::Vector3D rotation;
			AyumiMath::Quaternion orientation;
			AyumiMath::Vector3D scale;
			bool isVisible;
			bool isDead;
		};
	}
}
#endif
