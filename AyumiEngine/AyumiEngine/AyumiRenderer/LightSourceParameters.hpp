/**
 * File contains declaration of LightSourceParameters structure.
 * @file    LightSourceParameters.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-05-13
 */

#ifndef LIGHTSOURCEPARAMETERS_HPP
#define LIGHTSOURCEPARAMETERS_HPP

#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Structure represents Light color parameters structure: ambient, diffuse, specular RGBA values.
		 */
		struct LightSourceParameters
		{
			AyumiMath::Vector4D ambient;
			AyumiMath::Vector4D diffuse;
			AyumiMath::Vector4D specular;
		};
	}
}
#endif
