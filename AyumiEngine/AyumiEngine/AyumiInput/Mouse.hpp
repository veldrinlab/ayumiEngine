/**
 * File contains declaraion of Mouse class.
 * @file    Mouse.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-13
 */

#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <map>

#include "InputDevice.hpp"
#include "InputMouseButton.hpp"

namespace AyumiEngine
{
	namespace AyumiInput
	{
		typedef std::map<InputMouseButton, InputAction*> MouseInput;

		/**
		 * Class represents one of AyumiEngine input devices - Mouse. Class store std::map structure of
		 * all posibile device signals connected with signal id. In this case it is map of InputButton and InputAction.
		 * Class also store signlas of mouse move and mouse wheel move signal. On initialize all signlas is connected 
		 * with null action slot. Class deliver interface to connect user define methods with chosen key/move/move whell
		 * or disconnect it.
		 */
		class Mouse : public InputDevice
		{
		private:
			MouseInput* buttonMap;
			InputMoveAction* mouseMoveSignal;
			InputMoveWheelAction* mouseWheelMoveSignal;

		public:
			Mouse();
			~Mouse();

			void initializeDevice();

			void connectAction(const InputMouseButton& button,boost::function<void ()> method);
			void connectMoveAction(boost::function<void (int,int)> method);
			void connectMoveWheelAction(boost::function<void (int)> method);
			void disconnectAction(const InputMouseButton& button);
			void disconnectMoveAction();
			void disconnectMoveWheelAction();

			MouseInput* getButtonMap() const;
			InputMoveAction* getMouseMoveSignal() const;
			InputMoveWheelAction* getMouseWheelMoveSignal() const;
		};
	}
}
#endif
