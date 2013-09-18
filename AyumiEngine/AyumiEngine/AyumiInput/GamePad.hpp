/**
 * File contains declaration of GamePad class.
 * @file    GamePad.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-13
 */

#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP

#include <map>

#include "InputDevice.hpp"
#include "InputAxis.hpp"
#include "InputPadButton.hpp"

namespace AyumiEngine
{
	namespace AyumiInput
	{
		typedef std::map<InputAxis, InputAxisAction*> PadAxisInput;
		typedef std::map<InputPadButton, InputAction*> PadButtonInput;

		/**
		 * Class represents one of AyumiEngine input devices - . Class store std::map structure of
		 * all posibile device signals connected with signal id. In this case it is maps of InputAxis with InputAxisAction
		 * and InputPadButton with InputAction. On initialize all signlas is connected with null action slot.
		 * Class deliver interface to connect user defined methods with chosen axis/button or disconnect it.
		 */
		class GamePad : public InputDevice
		{
		private:
			PadAxisInput* axisMap;
			PadButtonInput* buttonMap;

		public:
			GamePad();
			~GamePad();

			void initializeDevice();

			void connectAction(const InputPadButton& button,boost::function<void ()> method);
			void connectMoveAxisAction(const InputAxis& axis, boost::function<void (float)> method);
			void disconnectAction(const InputPadButton& button);
			void disconnectMoveAxisAction(const InputAxis& axis);

			PadAxisInput* getAxisMap() const;
			PadButtonInput* getButtonMap() const;
		};
	}
}
#endif
