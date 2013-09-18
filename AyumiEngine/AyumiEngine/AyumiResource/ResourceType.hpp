/**
 * File contains declaration of ResourceType enumeration.
 * @file    ResourceType.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-15
 */

#ifndef RESOURCETYPE_HPP
#define RESOURCETYPE_HPP

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Enumeration represents all available Engine Resources. Each Resource type has
		 * own specialized Manager class to load and store data.
		 */
		enum ResourceType
		{
			TEXTURE,
			MESH,
			SHADER,
		};
	}
}
#endif
