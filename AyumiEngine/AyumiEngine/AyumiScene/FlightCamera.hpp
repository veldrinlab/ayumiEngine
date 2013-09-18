/**
 * File contains declaration of FlightCamera class.
 * @file    FlightCamera.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-08
 */

#ifndef FLIGHTCAMERA_HPP
#define FLIGHTCAMERA_HPP

#include "Camera.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class represents FlightCamera which can be used in space/flight simulator games with FPP and TPP
		 * view(for example from spacechip cocpit). Like FirstPersonCamera it extends Camera class by physics
		 * parameters like velocity and acceleration. The only difference with FPP camera is that FlightCamera
		 * straight to view direction and it rotate left/right in z order instead of strafe movement. FlightCamera
		 * needs keyboard and mouse to control. User must connect input devices signals with class methods methods.
		 */
		class FlightCamera : public Camera
		{
		private:
			AyumiMath::Vector3D velocity;
			AyumiMath::Vector3D rotationVelocity;
			AyumiMath::Vector3D acceleration;
			AyumiMath::Vector3D rotationAcceleration;
			AyumiMath::Vector3D positionDelta;
			float cameraSensivity;

		public:
			FlightCamera(const AyumiMath::Vector3D& position, const AyumiMath::Vector3D& viewDirection);
			~FlightCamera();

			void updatePosition(const float elapsedTime);
			void moveCameraForward();
			void moveCameraBack();
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
