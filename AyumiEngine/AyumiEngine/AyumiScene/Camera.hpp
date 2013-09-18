/**
 * File contains declaration of Camera class.
 * @file    Camera.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../AyumiMath/CommonMath.hpp"
#include "../AyumiCore/Configuration.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class represents base class of all Engine Camera classes. It stores basic camera parameters like
		 * poistion, view direction and projection frustrum parameters. Camera is abstract class which
		 * stores some pure abstarct methods which all derived classes must extend.
		 */
		class Camera
		{
		protected: 
			GLdouble fovy;
			GLdouble aspect;
			GLfloat near;
			AyumiMath::Vector3D position;
			AyumiMath::Vector3D viewDirection;
			AyumiMath::Quaternion orientation;

		public:
			AyumiMath::Vector3D rotation;	
			AyumiMath::Vector3D lastPosition;
			GLfloat far;

			virtual ~Camera() {};
			virtual void updatePosition(const float elapsedTime) = 0;
			virtual void setViewMatrix(AyumiMath::Matrix4D* viewMatrix) = 0;
			virtual void setProjectionMatrix(AyumiMath::Matrix4D* projectionMatrix) = 0;

			/**
			 * Accesor to camera view direction
			 * @return	camera view direction vector.
			 */
			AyumiMath::Vector3D getViewDirection() const
			{
				return viewDirection;
			}

			/**
			 * Accesor to camera position.
			 * @return	camera position vector.
			 */
			AyumiMath::Vector3D getPosition() const
			{
				return position;
			}

			/**
			 * Accesor to camera orientation.
			 * @return camera orientation quaternion.
			 */
			AyumiMath::Quaternion getOrientation() const
			{
				return orientation;
			}

			/**
			 * Setter of camera projection frustrum parameters.
			 * @param	fovy is camera frustrum clipping  fovy.
			 * @param	apect is camera frustrum clipping  aspect.
			 * @param	near is camera frustrum clipping near.
			 * @param	far is camera frustrum clipping far.
			 */
			void setProjectionParameters(const GLdouble fovy, const GLdouble aspect, const GLfloat near, const GLfloat far)
			{
				this->fovy = fovy;
				this->aspect = aspect;
				this->near = near;
				this->far = far;
			}

			/**
			 * Setter of camera position.
			 * @param	x is camera position vector x value.
			 * @param	y is camera position vector y value.
			 * @param	z is camera position vector z value.
			 */
			void setPosition(const float x, const float y, const float z)
			{
				position.set(x,y,z);
			}

			/**
			 * Setter of camera view direction.
			 * @param	x is camera view direction vector x value.
			 * @param	y is camera view direction vector y value.
			 * @param	z is camera view direction vector z value.
			 */
			void setViewDirection(const float x, const float y, const float z)
			{
				viewDirection.set(x,y,z);
			}

			/**
			 * Setter of camera rotation.
			 * @param	x is camera rotation vector x value.
			 * @param	y is camera rotation vector y value.
			 * @param	z is camera rotation vector z value.
			 */
			void setRotation(const float x, const float y, const float z)
			{
				rotation.set(x,y,z);
			}
		};
	}
}
#endif
