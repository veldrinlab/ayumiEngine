/**
 * File contains declaraion of Keyboard class.
 * @file    Keyboard.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <map>

#include "InputDevice.hpp"
#include "InputKey.hpp"

namespace AyumiEngine
{
	namespace AyumiInput
	{
		typedef std::map<InputKey, InputAction*> KeyboardInput;

		/**
		 * Class represents one of AyumiEngine input devices - Keyboard. Class store std::map structure of
		 * all posibile device signals connected with signal id. In this case it is map of InputKey and InputAction.
		 * On initialize all signlas is connected with null action slot. Class deliver interface to connect user defined
		 * methods with chosen key or disconnect it.
		 */
		class Keyboard : public InputDevice
		{
		private:
			KeyboardInput* keyMap;
		public:
			Keyboard();
			~Keyboard();

			void initializeDevice();

			void connectAction(const InputKey& key, boost::function<void ()> method);
			void disconnectAction(const InputKey& key);

			KeyboardInput* getKeyMap() const;
		};
	}
}
#endif
