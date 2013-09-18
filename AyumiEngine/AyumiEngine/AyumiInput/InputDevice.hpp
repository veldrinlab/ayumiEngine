/**
 * File contains declaraion of InputDevice abstract class.
 * @file    InputDevice.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-13
 */

#ifndef INPUTDEVICE_HPP
#define INPUTDEVICE_HPP

#include <SFML/Window.hpp>

#include "InputAction.hpp"
#include "InputMoveAction.hpp"

namespace AyumiEngine
{
	namespace AyumiInput
	{
		/**
		 * Class represents abstract interface of all AyumiEngine Input Devices like Keyboard or Mouse.
		 * All devices must extend this class by implementing pure virtual initializeDevice() method. Interface
		 * deliver also default null action methods which is used to initliaze slots for device signlas. 
		 */
		class InputDevice
		{
		public:
			virtual void initializeDevice() = 0;
			void nullAction() {};
			void nullMoveAction(const int x, const int y) {};
			void nullWhellMoveAction(const int delta) {};
			void nullAxisMoveAction(const float position) {};
		};
	}
}
#endif
