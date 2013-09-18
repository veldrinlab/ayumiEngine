/**
 * File contains declaration of DirectionalLight structure.
 * @file    DirectionalLight.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-05-13
 */

#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include <string>

#include "LightType.hpp"
#include "LightSourceParameters.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Structure represents forward rendering DirectionalLight light source structure. Is store light type,
		 * parameters and direction.
		 */
		struct DirectionalLight
		{
			std::string name;
			LightType type;
			LightSourceParameters color;
			AyumiMath::Vector3D direction;
		};
	}
}
#endif
