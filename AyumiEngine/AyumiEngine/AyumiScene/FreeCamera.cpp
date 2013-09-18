/**
 * File contains definition of FreeCamera class.
 * @file    FreeCamera.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-08
 */

#include "FreeCamera.hpp"

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
		FreeCamera::FreeCamera(const Vector3D& position, const Vector3D& viewDirection)
		{
			const double width = static_cast<GLdouble>(Configuration::getInstance()->getResolutionWidth());
			const double height = static_cast<GLdouble>(Configuration::getInstance()->getResolutionHeight());

			fovy = 45.0;
			aspect = width/height;
			near = 0.1f;
			far = 100000.0f;

			this->position = position;
			this->viewDirection = viewDirection;
	
			rotation.set(0.0f,0.0f,0.0f);
			velocity.set(0.0f,0.0f,0.0f);
			acceleration.set(0.0f,0.0f,0.0f);
			rotationVelocity.set(0.0f,0.0f,0.0f);
			rotationAcceleration.set(0.0f,0.0f,0.0f);
			cameraSensivity = 0.1f;	
		}

		/**
		 * Class destructor, free allocated memory. Nothing to delete.
		 */
		FreeCamera::~FreeCamera()
		{

		}

		/**
		 * Method is used to update camera position.
		 * @param	elapsedTime is time between frames in seconds.
		 */
		void FreeCamera::updatePosition(const float elapsedTime)
		{
			position += positionDelta * elapsedTime;
			positionDelta.set(0.0f,0.0f,0.0f);  
		}

		/**
		 * Method is used to move camera forward. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void FreeCamera::moveCameraForward()
		{
			positionDelta[0] -= viewDirection[0] * velocity[0];
			positionDelta[1] -= viewDirection[1] * velocity[1];
			positionDelta[2] -= viewDirection[2] * velocity[2];
		}

		/**
		 * Method is used to move camera back. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void FreeCamera::moveCameraBack()
		{
			positionDelta[0] += viewDirection[0] * velocity[0];
			positionDelta[1] += viewDirection[1] * velocity[1];
			positionDelta[2] += viewDirection[2] * velocity[2];
		}

		/**
		 * Method is used to move camera up. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void FreeCamera::moveCameraUp()
		{
			positionDelta[1] -= -1.0f * velocity[1];
		}

		/**
		 * Method is used to move camera down. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void FreeCamera::moveCameraDown()
		{
			positionDelta[1] += -1.0f * velocity[1];
		}

		/**
		 * Method is used to rotate camera left. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void FreeCamera::rotateCameraLeft()
		{
			rotation[1] -= rotationVelocity[1];
		}

		/**
		 * Method is used to rotate camera right. It is one of class sockets, which can
		 * be connected with input device signals.
		 */
		void FreeCamera::rotateCameraRight()
		{
			rotation[1] += rotationVelocity[1];
		}

		/**
		 * Method is used to change camera view target vector. It is one of class coket, which
		 * can be connected with input device signals(mouse, game pad). Method translate position
		 * of input device pointer on screen to rotation vector.
		 * @param	x is input device pointer x value.
		 * @param	y is input device pointer y value.
		 */
		void FreeCamera::changeViewTarget(int x, int y)
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
		void FreeCamera::setViewMatrix(Matrix4D* viewMatrix)
		{
			viewMatrix->LoadIdentity();
			Quaternion rotate(Vector3D( 1.0f, 0.0f, 0.0f ),rotation[0]);
			rotate *= Quaternion(Vector3D( 0.0f, 1.0f, 0.0f ),rotation[1]);
			rotate *= Quaternion(Vector3D( 0.0f, 0.0f, 1.0f ),rotation[2]);
			*viewMatrix *= rotate.matrix4();
			orientation = rotate;
			viewMatrix->Translatef(-position.x(),-position.y(),-position.z());
			viewDirection.set(viewMatrix->data()[8],viewMatrix->data()[9],viewMatrix->data()[10]);
		}

		/**
		 * Method is used to set Renderer module projection matrix.
		 * @param	projectionMatrix is pointer to Renderer projection matrix.
		 */
		void FreeCamera::setProjectionMatrix(Matrix4D* projectionMatrix)
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
		void FreeCamera::setVelocity(const float x, const float y, const float z)
		{
			velocity.set(x,y,z);
		}

		/**
		 * Setter of camera acceleration.
		 * @param	x is camera acceleration vector x value.
		 * @param	y is camera acceleration vector y value.
		 * @param	z is camera acceleration vector z value.
		 */
		void FreeCamera::setAcceleration(const float x, const float y, const float z)
		{
			acceleration.set(x,y,z);
		}

		/**
		 * Setter of camera rotate velocity.
		 * @param	x is camera rotate velocity vector x value.
		 * @param	y is camera rotate velocity vector y value.
		 * @param	z is camera rotate velocity vector z value.
		 */
		void FreeCamera::setRotateVelocity(const float x, const float y, const float z)
		{
			rotationVelocity.set(x,y,z);
		}

		/**
		 * Setter of camera rotate acceleration.
		 * @param	x is camera rotate acceleration vector x value.
		 * @param	y is camera rotate acceleration vector y value.
		 * @param	z is camera rotate acceleration vector z value.
		 */
		void FreeCamera::setRotateAcceleration(const float x, const float y, const float z)
		{
			rotationAcceleration.set(x,y,z);
		}
	}
}
