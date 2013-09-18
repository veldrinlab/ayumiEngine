/**
 * File contains declaration of FreeCamera class.
 * @file    FreeCamera.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-08
 */

#ifndef FREECAMERA_HPP
#define FREECAMERA_HPP

#include "Camera.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class represents FreeCamera which is very useful in scene creating tools, testing, debugging
		 * and creating some "ghost" entity in game replays or multi-player games breaks. Like FirstPersonCamera
		 * it extends Camera class by physics parameters like velocity and acceleration. The only difference with
		 * FPP camera is that FreeCamera allows to move up and down, straight to view direction and it rotate left/right
		 * instead of strafe movement. FreeCamera needs keyboard and mouse to control. User must connect input devices
		 * signals with class methods methods.
		 */
		class FreeCamera : public Camera
		{
		private:
			AyumiMath::Vector3D velocity;
			AyumiMath::Vector3D rotationVelocity;
			AyumiMath::Vector3D acceleration;
			AyumiMath::Vector3D rotationAcceleration;
			AyumiMath::Vector3D positionDelta;
			float cameraSensivity;

		public:
			FreeCamera(const AyumiMath::Vector3D& position, const AyumiMath::Vector3D& viewDirection);
			~FreeCamera();

			void updatePosition(const float elapsedTime);
			void moveCameraForward();
			void moveCameraBack();
			void moveCameraUp();
			void moveCameraDown();
			void rotateCameraLeft();
			void rotateCameraRight();
			void changeViewTarget(int x, int y);
			void setViewMatrix(AyumiMath::Matrix4D* viewMatrix);
			void setProjectionMatrix(AyumiMath::Matrix4D* projectionMatrix);
			void setVelocity(const float x, const float y, const float z);
			void setAcceleration(const float x, const float y, const float z);
			void setRotateVelocity(const float x, const float y, const float z);
			void setRotateAcceleration(const float x, const float y, const float z);
		};
	}
}
#endif
