/**
 * File contains declaration of SpotLight structure.
 * @file    SpotLight.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-05-13
 */

#ifndef SPOTLIGHT_HPP
#define	SPOTLIGHT_HPP

#include <string>

#include "LightType.hpp"
#include "LightSourceParameters.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Structure represents forward rendering SpotLight light source structure. Is store light type,
		 * parameters, cone data, position and direction.
		 */
		struct SpotLight
		{
			std::string name;
			LightType type;
			LightSourceParameters color;
			float range;
			float cosInnerCone;
			float cosOuterCone;
			AyumiMath::Vector3D position;
			AyumiMath::Vector3D direction;
		};
	}
}
#endif
