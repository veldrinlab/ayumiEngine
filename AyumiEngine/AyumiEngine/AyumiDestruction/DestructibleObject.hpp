/**
 * File contains declaraion of DestructibleObject structure.
 * @file    DestructibleObject.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef DESTRUCTIBLEOBJECT_HPP
#define DESTRUCTIBLEOBJECT_HPP

#include <string>

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		/**
		 * Structure represents one part of destructible object. Store all necessary data like
		 * connected objects name and force value which is nedd to destroy connection.
		 */
		struct DestructibleObject
		{
			std::string firstPart;
			std::string secondPart;
			float force;
			float torque;
			
			/**
			 * Class constructor with intiialize parameters.
			 * @param	first is name of first object.
			 * @param	second is name of second object.
			 * @param	force is break force value.
			 * @param	torque is break torque value.
			 */
			DestructibleObject(const std::string& first, const std::string& second, const float force, const float torque)
			{
				firstPart = first;
				secondPart = second;
				this->force = force;
				this->torque = torque;
			}
		};
	}
}
#endif
