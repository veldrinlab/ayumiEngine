/**
 * File contains declaration of StaticCamera class.
 * @file    StaticCamera.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#ifndef STATICCAMERA_HPP
#define STATICCAMERA_HPP

#include "Camera.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class represents Static camera which is the only static camera - user can only set camera position,
		 * rotation, and vier direction. It can be used in many 2D games and some type of 3D games for example
		 * Space Invaders 3D. Camera don't need any input devices.
		 */
		class StaticCamera : public Camera
		{
		public:
			StaticCamera();
			~StaticCamera();

			void updatePosition(const float elapsedTime);
			void setViewMatrix(AyumiMath::Matrix4D* viewMatrix);
			void setProjectionMatrix(AyumiMath::Matrix4D* projectionMatrix);
		};
	}
}
#endif
