/**
 * File contains definition of ThirdPersonCamera class.
 * @file    ThirdPersonCamera.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-08
 */

#include "ThirdPersonCamera.hpp"

using namespace AyumiEngine::AyumiCore;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class constructor with initialize parameters.
		 * @param	entity is pointer to SceneEntity which will be connected with camera.
		 * @param	position is camera position vector.
		 * @param	viewDirection is camera view direction vector.
		 */
		ThirdPersonCamera::ThirdPersonCamera(SceneEntity* entity,const Vector3D& position, const Vector3D& viewDirection)
		{
			const double width = static_cast<GLdouble>(Configuration::getInstance()->getResolutionWidth());
			const double height = static_cast<GLdouble>(Configuration::getInstance()->getResolutionHeight());

			fovy = 45.0;
			aspect = width/height;
			near = 0.1f;
			far = 100000.0f;
			
			this->entity = entity;
			this->position = position;
			this->viewDirection = viewDirection;
	
			rotation.set(0.0f,0.0f,0.0f);
			velocity.set(0.0f,0.0f,0.0f);
			acceleration.set(0.0f,0.0f,0.0f);
			cameraSensivity = 0.1f;	
		}

		/**
		 * Class destructor, free allocated memory. Nothing to delete.
		 */
		ThirdPersonCamera::~ThirdPersonCamera()
		{

		}

		/**
		 * Method is used to update camera and entity position.
		 * @param	elapsedTime is time between frames in seconds.
		 */
		void ThirdPersonCamera::updatePosition(const float elapsedTime)
		{
			//TODO moze jakis slerp machnac zobaczymy
			position += positionDelta * elapsedTime;
			positionDelta.set(0.0f,0.0f,0.0f);

			//TODO jakies parametry odleg³oœci entity
			Vector3D entityPosition = position;
			entityPosition[0] -= viewDirection[0] * 5.0f * velocity[0];
			entityPosition[1] -= 40.0f;
			entityPosition[2] -= viewDirection[2] * 5.0f * velocity[2];

			//entity->entityState.rotation.set(-90.0f,0,90.0f-rotation[1]);

			entity->entityState.position.set(entityPosition[0],entityPosition[1],entityPosition[2]);

		}

		/**
		 * Method is used to move camera forward. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void ThirdPersonCamera::moveCameraForward()
		{
			positionDelta[0] -= viewDirection[0] * velocity[0];
			positionDelta[2] -= viewDirection[2] * velocity[2];
		}

		/**
		 * Method is used to move camera back. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void ThirdPersonCamera::moveCameraBack()
		{
			positionDelta[0] += viewDirection[0] * velocity[0];
			positionDelta[2] += viewDirection[2] * velocity[2];
		}

		/**
		 * Method is used to change camera view target vector. It is one of class coket, which
		 * can be connected with input device signals(mouse, game pad). Method translate position
		 * of input device pointer on screen to rotation vector.
		 * @param	x is input device pointer x value.
		 * @param	y is input device pointer y value.
		 */
		void ThirdPersonCamera::changeViewTarget(int x, int y)
		{
			int dx = Configuration::getInstance()->getResolutionWidth()/2 - x;
			int dy = -(Configuration::getInstance()->getResolutionHeight()/2 - y);

			rotation[1] -= dx * cameraSensivity;
			rotation[0] += dy * cameraSensivity;
		}

		/**
		 * Method is used to set Renderer module view matrix.
		 * @param	viewMatrix is pointer to Renderer view matrix.
		 */
		void ThirdPersonCamera::setViewMatrix(Matrix4D* viewMatrix)
		{
			viewMatrix->LoadIdentity();
			Quaternion rotate(Vector3D( 1.0f, 0.0f, 0.0f ),rotation[0]);
			rotate *= Quaternion(Vector3D( 0.0f, 1.0f, 0.0f ),rotation[1]);
			rotate *= Quaternion(Vector3D( 0.0f, 0.0f, 1.0f ),rotation[2]);
			orientation = rotate;
			*viewMatrix *= rotate.matrix4();
			viewMatrix->Translatef(-position.x(),-position.y(),-position.z());
			viewDirection.set(viewMatrix->data()[8],viewMatrix->data()[9],viewMatrix->data()[10]);
		}

		/**
		 * Method is used to set Renderer module projection matrix.
		 * @param	projectionMatrix is pointer to Renderer projection matrix.
		 */
		void ThirdPersonCamera::setProjectionMatrix(Matrix4D* projectionMatrix)
		{
			projectionMatrix->LoadIdentity();
			projectionMatrix->Perspective(fovy,aspect,near,far);
		}

		/**
		 * Setter of camera velocity.
		 * @param	x is camera velocity vector x value.
		 * @param	y is camera velocity vector y value.
		 * @param	z is camera velocity vector z value.
		 */
		void ThirdPersonCamera::setVelocity(const float x, const float y, const float z)
		{
			velocity.set(x,y,z);
		}

		/**
		 * Setter of camera acceleration.
		 * @param	x is camera acceleration vector x value.
		 * @param	y is camera acceleration vector y value.
		 * @param	z is camera acceleration vector z value.
		 */
		void ThirdPersonCamera::setAcceleration(const float x, const float y, const float z)
		{
			acceleration.set(x,y,z);
		}
	}
}
