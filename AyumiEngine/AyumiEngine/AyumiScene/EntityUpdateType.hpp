/**
 * File contains declaration of EntityUpdateType enumeration.
 * @file    EntityUpdateType.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-08
 */

#ifndef ENTITYUPDATETYPE_HPP
#define ENTITYUPDATETYPE_HPP

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Enumeration represents all available SceneEntity update types: extending,
		 * script and funtor.
		 */
		enum EntityUpdateType
		{
			NONE,
			SCRIPT,
			FUNCTION,
			EXTENDING
		};
	}
}
#endif
