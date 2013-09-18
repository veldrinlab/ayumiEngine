/**
 * File contains definition of StaticCamera class.
 * @file    StaticCamera.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#include "StaticCamera.hpp"

using namespace AyumiEngine::AyumiCore;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class default constructor. Set camera default parameters.
		 */
		StaticCamera::StaticCamera()
		{
			const double width = static_cast<GLdouble>(Configuration::getInstance()->getResolutionWidth());
			const double height = static_cast<GLdouble>(Configuration::getInstance()->getResolutionHeight());

			fovy = 45.0;
			aspect = width/height;
			near = 0.1f;
			far = 10000.0f;
		}

		/**
		 * Class destructor, free allocated memory. Nothing to delete.
		 */
		StaticCamera::~StaticCamera()
		{
			
		}
		
		/**
		 * Method is used to update camera position. Camera is static.
		 * @param	elapsedTime is time between frames in seconds.
		 */
		void StaticCamera::updatePosition(const float elapsedTime)
		{
			 
		}

		/**
		 * Method is used to set Renderer module view matrix.
		 * @param	viewMatrix is pointer to Renderer view matrix.
		 */
		void StaticCamera::setViewMatrix(AyumiMath::Matrix4D* viewMatrix)
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
		void StaticCamera::setProjectionMatrix(AyumiMath::Matrix4D* projectionMatrix)
		{
			projectionMatrix->LoadIdentity();
			projectionMatrix->Perspective(fovy,aspect,near,far);
		}
	}
}
