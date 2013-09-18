/**
 * File contains declaration of ShadowMap structure.
 * @file    ShadowMap.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-10
 */

#ifndef SHADOWMAP_HPP
#define SHADOWMAP_HPP

#include "../AyumiUtils/FrameBufferObject.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Structure represents shadow map data which is used in simple shadow mapping algorithm.
		 */
		struct ShadowMap
		{
			int shadowMapWidth;
			int shadowMapHeight;
			GLuint frameBuffer;
			GLuint depthTexture;
			AyumiMath::Matrix4D lightMatrix;
			AyumiMath::Matrix4D shadowMatrix;
			AyumiMath::Matrix4D bias;
			AyumiMath::Vector3D position;
			AyumiMath::Vector3D direction;
			std::string textureName;
			std::string matrixName;
		};
	}
}
#endif
