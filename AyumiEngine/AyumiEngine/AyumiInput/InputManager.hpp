/**
 * File contains declaraion of InputManager class.
 * @file    InputManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-13
 */

#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <boost/signal.hpp>
#include <boost/bind.hpp>

#include <SFML/System/Vector2.hpp>

#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "GamePad.hpp"

#include "..\AyumiCore\ContextManager.hpp"

namespace AyumiEngine
{
	typedef sf::Event AyumiEvent;

	namespace AyumiInput
	{
		/**
		 * Class represents one of main AyumiEngine modules - InputManager which is responsible for the
		 * user input action handling. InputManager controls receiving context window event and translate them
		 * to input devices signals. Class controls signals of Keyboard, Mouse and GamePad devices and store public interface
		 * to connect and disconnect device signlas with user defined funtions.
		 */
		class InputManager
		{
		private:
			AyumiCore::ContextManager* engineContext;
			AyumiEvent event;
			Keyboard* keyboardDevice; 
			Mouse* mouseDevice;
			GamePad* padDevice;

		public:
			InputManager(AyumiCore::ContextManager* engineContext);
			~InputManager();

			void initializeInputManager();
			void updateInput();

			void connectKeyboardAction(const InputKey& key, boost::function<void ()> method);
			void connectMouseAction(const InputMouseButton& button, boost::function<void ()> method);
			void connectMouseMoveAction(boost::function<void (int,int)> method);
			void connectPadAction(const InputPadButton& button, boost::function<void ()> method);
			void connectMoveAxisAction(const InputAxis& axis, boost::function<void (float)> method);

			void disconnectKeyboardAction(const InputKey& key);
			void disconnectMoveAction();
			void disconnectMoveWheelAction();
			void disconnectPadAction(const InputPadButton& button);
			void disconnectMoveAxisAction(const InputAxis& axis);
		};
	}
}
#endif
