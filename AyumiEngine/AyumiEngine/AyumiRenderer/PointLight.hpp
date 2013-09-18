/**
 * File contains declaration of PointLight structure.
 * @file    PointLight.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-05-13
 */

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include <string>

#include "LightType.hpp"
#include "LightSourceParameters.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Structure represents forward rendering PointLight light source structure. Is store light type,
		 * parameters, radius and position.
		 */
		struct PointLight
		{
			std::string name;
			LightType type;
			LightSourceParameters color;
			float radius;
			AyumiMath::Vector3D position;
		};
	}
}
#endif
