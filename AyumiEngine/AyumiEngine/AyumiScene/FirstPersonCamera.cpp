/**
 * File contains definition of FirstPersonCamera class.
 * @file    FirstPersonCamera.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#include "FirstPersonCamera.hpp"
	
using namespace AyumiEngine::AyumiCore;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class constructor with initialize parameters.
		 * @param	position is camera position vector.
		 * @param	viewDirection is camera view direction vector.
		 */
		FirstPersonCamera::FirstPersonCamera(const Vector3D& position, const Vector3D& viewDirection)
		{
			const double width = static_cast<GLdouble>(Configuration::getInstance()->getResolutionWidth());
			const double height = static_cast<GLdouble>(Configuration::getInstance()->getResolutionHeight());

			fovy = 45.0;
			aspect = width/height;
			near = 1.0f;
			far = 500.0f;

			this->position = position;
			this->viewDirection = viewDirection;
	
			rotation.set(viewDirection[0],viewDirection[1],viewDirection[2]);
			velocity.set(0.0f,0.0f,0.0f);
			acceleration.set(0.0f,0.0f,0.0f);
			strafeDirection.set(1.0f,0.0f,0.0f);
			cameraSensivity = 0.1f;	
		}

		/**
		 * Class destructor, free allocated memory. Nothing to delete.
		 */
		FirstPersonCamera::~FirstPersonCamera()
		{

		}

		/**
		 * Method is used to update camera position.
		 * @param	elapsedTime is time between frames in seconds.
		 */
		void FirstPersonCamera::updatePosition(const float elapsedTime)
		{
			lastPosition = position;
			position += positionDelta * elapsedTime;
			positionDelta.set(0.0f,0.0f,0.0f);		
		}

		/**
		 * Method is used to move camera forward. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void FirstPersonCamera::moveCameraForward()
		{
			positionDelta[0] -= viewDirection[0] * velocity[0];
			positionDelta[2] -= viewDirection[2] * velocity[2];
		}

		/**
		 * Method is used to move camera back. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void FirstPersonCamera::moveCameraBack()
		{
			positionDelta[0] += viewDirection[0] * velocity[0];
			positionDelta[2] += viewDirection[2] * velocity[2];
		}

		/**
		 * Method is used to move camera left. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void FirstPersonCamera::moveCameraLeft()
		{
			positionDelta[0] -= strafeDirection[0] * velocity[0];
			positionDelta[2] -= strafeDirection[2] * velocity[2];
		}

		/**
		 * Method is used to move camera right. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void FirstPersonCamera::moveCameraRight()
		{
			positionDelta[0] += strafeDirection[0] * velocity[0];
			positionDelta[2] += strafeDirection[2] * velocity[2];			
		}

		/**
		 * Method is used to change camera view target vector. It is one of class coket, which
		 * can be connected with input device signals(mouse, game pad). Method translate position
		 * of input device pointer on screen to rotation vector.
		 * @param	x is input device pointer x value.
		 * @param	y is input device pointer y value.
		 */
		void FirstPersonCamera::changeViewTarget(int x, int y)
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
		void FirstPersonCamera::setViewMatrix(Matrix4D* viewMatrix)
		{
			viewMatrix->LoadIdentity();

			Quaternion rotate(Vector3D( 1.0f, 0.0f, 0.0f ),rotation[0]);
			rotate *= Quaternion(Vector3D( 0.0f, 1.0f, 0.0f ),rotation[1]);
			rotate *= Quaternion(Vector3D( 0.0f, 0.0f, 1.0f ),rotation[2]);
			*viewMatrix *= rotate.matrix4();
			orientation = rotate;
			viewMatrix->Translatef(-position.x(),-position.y(),-position.z());

			viewDirection.set(viewMatrix->data()[8],viewMatrix->data()[9],viewMatrix->data()[10]);
			strafeDirection.set(viewMatrix->data()[0],viewMatrix->data()[1],viewMatrix->data()[2]);
			up.set(viewMatrix->data()[4],viewMatrix->data()[5],viewMatrix->data()[6]);
		}

		/**
		 * Method is used to set Renderer module projection matrix.
		 * @param	projectionMatrix is pointer to Renderer projection matrix.
		 */
		void FirstPersonCamera::setProjectionMatrix(Matrix4D* projectionMatrix)
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
		void FirstPersonCamera::setVelocity(const float x, const float y, const float z)
		{
			velocity.set(x,y,z);
		}

		/**
		 * Setter of camera acceleration.
		 * @param	x is camera acceleration vector x value.
		 * @param	y is camera acceleration vector y value.
		 * @param	z is camera acceleration vector z value.
		 */
		void FirstPersonCamera::setAcceleration(const float x, const float y, const float z)
		{
			acceleration.set(x,y,z);
		}
	}
}
