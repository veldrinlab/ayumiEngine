/**
 * File contains declaration of FirstPersonCamera class.
 * @file    FirstPersonCamera.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#ifndef FIRSTPERSONCAMERA_HPP
#define FIRSTPERSONCAMERA_HPP

#include "Camera.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class represents First person camera which is basic part of all First Person Shooter type games
		 * and many adventure games. It extends Camera class by physics parametres like velocity, acceleration
		 * and strafe direction which is nesseccary in shootres. FirstPersonCamera needs keyboard and mouse
		 * to control. User must connect input devices signals with class methods.
		 */
		class FirstPersonCamera : public Camera
		{
		private:
			AyumiMath::Vector3D velocity;
			AyumiMath::Vector3D acceleration;
			AyumiMath::Vector3D strafeDirection;
			AyumiMath::Vector3D positionDelta;
			float cameraSensivity;
		public:
			FirstPersonCamera(const AyumiMath::Vector3D& position, const AyumiMath::Vector3D& viewDirection);
			~FirstPersonCamera();

			void updatePosition(const float elapsedTime);
			void moveCameraForward();
			void moveCameraBack();
			void moveCameraLeft();
			void moveCameraRight();
			void changeViewTarget(int x, int y);
			void setViewMatrix(AyumiMath::Matrix4D* viewMatrix);
			void setProjectionMatrix(AyumiMath::Matrix4D* projectionMatrix);
			void setVelocity(const float x, const float y, const float z);
			void setAcceleration(const float x, const float y, const float z);

			AyumiMath::Vector3D getStrafeDirection() const
			{
				return strafeDirection;
			}

			AyumiMath::Vector3D up;

		};
	}
}
#endif
