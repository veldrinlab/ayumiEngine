/**
 * File contains declaration of TransformationMatrices structure.
 * @file    TransformationMatrices.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-18
 */

#ifndef TRANSFORMATIONMATRICES_HPP
#define TRANSFORMATIONMATRICES_HPP

#include "../AyumiResource/Shader.hpp"
#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Structure represents package of 3D transformation matrices.
		 */
		struct TransformationMatrices
		{
			AyumiMath::Matrix4D modelMatrix;
			AyumiMath::Matrix4D viewMatrix;
			AyumiMath::Matrix4D projectionMatrix;
			AyumiMath::Matrix4D modelViewMatrix;
			AyumiMath::Matrix3D normalMatrix;
			AyumiMath::Matrix4D inverseViewMatrix;

			void reset()
			{
				modelMatrix.LoadIdentity();
				modelViewMatrix.LoadIdentity();
				normalMatrix.identity();
			}


			/**
			 * Method is used to create normal matrix from model view matrix. Normal Matrix is used in
			 * materials like bump/normal or parallax mapping.
			 */
			void createNormalMatrix()
			{
				AyumiMath::Matrix4D m = inverse(modelViewMatrix);
				normalMatrix = AyumiMath::Matrix3D(m[0],m[1],m[2],m[4],m[5],m[6],m[8],m[9],m[10]);	
			}

			/**
			 * Method is used to send matrices data to current shader.
			 * @param	shader is pointer to current using shader.
			 */
			void sendMatricesData(AyumiResource::Shader* shader)
			{
				shader->setUniformMatrix4fv("modelMatrix",modelMatrix.transpose().data());
				shader->setUniformMatrix4fv("viewMatrix",transpose(viewMatrix).data());
				shader->setUniformMatrix4fv("modelViewMatrix",modelViewMatrix.transpose().data());
				shader->setUniformMatrix4fv("projectionMatrix",projectionMatrix.data());
				shader->setUniformMatrix4fv("inverseCameraMatrix",inverseViewMatrix.data());
				shader->setUniformMatrix3fv("normalMatrix",normalMatrix.data());
			}
		};
	}
}
#endif
