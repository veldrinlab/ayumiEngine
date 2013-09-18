/**
 * File contains declaration and definition of LightType enumeration.
 * @file    LightType.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-05-13
 */

#ifndef LIGHTTYPE_HPP
#define LIGHTTYPE_HPP

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Enumeration represents all available light type.
		 */
		enum LightType
		{
			DIRECTIONAL,
			POINT,
			SPOT,
		};
	}
}
#endif
