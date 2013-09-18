/**
 * File contains declaration of ThirdPersonCamera class.
 * @file    ThirdPersonCamera.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-08
 */

#ifndef THIRDPERSONCAMERA_HPP
#define THIRDPERSONCAMERA_HPP

#include "Camera.hpp"
#include "SceneEntity.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class represents Third person camera which can be used int TPP shooters, RPG games and many other
		 * type of games. It extends Camera class by physics parametres like velocity, acceleration and rotation.
		 * Main difference between other cameras is that Third Person Camera is connected which SceneEntity.
		 * Position and rotation of camera is controlled by SceneEntity parameters. ThirdPersonCamera needs
		 * keyboard and mouse to control. User must connect input devices signals with lass methods.
		 */
		class ThirdPersonCamera : public Camera
		{
		private:
			SceneEntity* entity;
			AyumiMath::Vector3D velocity;
			AyumiMath::Vector3D acceleration;
			AyumiMath::Vector3D viewDirection;
			AyumiMath::Vector3D positionDelta;
			float cameraSensivity;

		public:
			ThirdPersonCamera(SceneEntity* entity,const AyumiMath::Vector3D& position, const AyumiMath::Vector3D& viewDirection);
			~ThirdPersonCamera();

			void updatePosition(const float elapsedTime);
			void moveCameraForward();
			void moveCameraBack();
			void changeViewTarget(int x, int y);
			void setViewMatrix(AyumiMath::Matrix4D* viewMatrix);
			void setProjectionMatrix(AyumiMath::Matrix4D* projectionMatrix);
			void setVelocity(const float x, const float y, const float z);
			void setAcceleration(const float x, const float y, const float z);
		};
	}
}
#endif
