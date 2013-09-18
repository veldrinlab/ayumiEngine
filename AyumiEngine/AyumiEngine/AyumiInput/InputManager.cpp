/**
 * File contains definition of InputManager class.
 * @file    InputManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-13
 */

#include "InputManager.hpp"

#include <iostream>

namespace AyumiEngine
{
	namespace AyumiInput
	{
		/**
		 * Class constructor with initialize parameter. It is used to create and initialize all start input devices.
		 * @param	engineContext is pointer to Engine context which register events.
		 */
		InputManager::InputManager(AyumiCore::ContextManager* engineContext)
		{
			this->engineContext = engineContext;
			keyboardDevice = new Keyboard();
			mouseDevice = new Mouse();
			padDevice = new GamePad();
		}

		/**
		 * Class destructor, free allocated memory for input device objects.
		 */
		InputManager::~InputManager()
		{
			delete keyboardDevice;
			delete mouseDevice;
			delete padDevice;
		}

		/**
		 * Method is used to initialize input manager devices.
		 */
		void InputManager::initializeInputManager()
		{
			keyboardDevice->initializeDevice();
			mouseDevice->initializeDevice();
			padDevice->initializeDevice();
		}

		/**
		 * Method is used to update input per frame. Manager translates all occured window events and
		 * emit events signals.
		 */
		void InputManager::updateInput()
		{
			while (engineContext->getContextWindow()->pollEvent(event))
			{
				switch(event.type)
				{
					case sf::Event::KeyPressed:
						keyboardDevice->getKeyMap()->at(static_cast<InputKey>(event.key.code))->signal();
						break;
					case sf::Event::MouseMoved:
						mouseDevice->getMouseMoveSignal()->signal(event.mouseMove.x,event.mouseMove.y);
						break;
					case sf::Event::MouseWheelMoved:
						mouseDevice->getMouseWheelMoveSignal()->signal(event.mouseWheel.delta);
						break;
					case sf::Event::MouseButtonPressed:		
						mouseDevice->getButtonMap()->at(static_cast<InputMouseButton>(event.mouseButton.button))->signal();
						break;
					case sf::Event::JoystickButtonPressed:
						padDevice->getButtonMap()->at(static_cast<InputPadButton>(event.joystickButton.button))->signal();
						break;
					case sf::Event::JoystickMoved:
						padDevice->getAxisMap()->at(static_cast<InputAxis>(event.joystickMove.axis))->signal(event.joystickMove.position);
						break;
					case sf::Event::Closed:
						exit(0);
					default:
						break;
				}
			}

			sf::Mouse::setPosition(sf::Vector2i(engineContext->getResolutionWidth()/2,engineContext->getResolutionHeight()/2),*engineContext->getContextWindow());
		}

		/**
		 * Method is used to connect Keyboard device signal with user defined slot function.
		 * @param	key is id of device signal, one of InputKey enumeration.
		 * @param	method is pointer to user defined slot, class method or function.
		 */
		void InputManager::connectKeyboardAction(const InputKey& key, boost::function<void ()> method)
		{
			keyboardDevice->connectAction(key, method);
		}

		/**
		 * Method is used to connect device signal with user defined slot function.
		 * @param	button is id of device signal, one of InputButton enumeration.
		 * @param	method is pointer to user defined slot, class method or function.
		 */
		void InputManager::connectMouseAction(const InputMouseButton& button, boost::function<void ()> method)
		{
			mouseDevice->connectAction(button, method);
		}

		/**
		 * Method is used to connect device wheel move signal with user defined slot function.
		 * @param	method is pointer to user defined slot, class method or function.
		 */
		void InputManager::connectMouseMoveAction(boost::function<void (int,int)> method)
		{
			mouseDevice->connectMoveAction(method);
		}

		/**
		 * Method is used to connect device signal with user defined slot function.
		 * @param	button is id of device signal, one of InputPadButton enumeration.
		 * @param	method is pointer to user defined slot, class method or function.
		 */
		void InputManager::connectPadAction(const InputPadButton& button, boost::function<void ()> method)
		{
			padDevice->connectAction(button,method);
		}

		/**
		 * Method is used to connect defined device axis move signal with user defined slot function.
		 * @param	axis is id of device signal, one of InputAxis enumeration.
		 * @param	method is pointer to user defined slot, class method or function.
		 */
		void InputManager::connectMoveAxisAction(const InputAxis& axis, boost::function<void (float)> method)
		{
			padDevice->connectMoveAxisAction(axis,method);
		}

		/**
		 * Method is used to disconnect device signal with all connected slots.
		 * @param	key is id of device signal, one of InputKey enumeration.
		 */
		void InputManager::disconnectKeyboardAction(const InputKey& key)
		{
			keyboardDevice->disconnectAction(key);
		}

		/**
		 * Method is used to disconnect device move signal with all connected slots and connect with
		 * null action again.
		 */
		void InputManager::disconnectMoveAction()
		{
			mouseDevice->disconnectMoveAction();
		}

		/**
		 * Method is used to disconnect device wheel move signal with all connected slots and connect with
		 * null action again.
		 */
		void InputManager::disconnectMoveWheelAction()
		{
			mouseDevice->disconnectMoveWheelAction();
		}

		/**
		 * Method is used to disconnect device signal with all connected slots and connect with
		 * null action again.
		 * @param	button is id of device signal, one of InputPadButton enumeration.
		 */
		void InputManager::disconnectPadAction(const InputPadButton& button)
		{
			padDevice->disconnectAction(button);
		}
		
		/**
		 * Method is used to disconnect device signal with all connected slots and connect with
		 * null action again.
		 * @param	axis is id of device signal, one of InputAxis enumeration.
		 */
		void InputManager::disconnectMoveAxisAction(const InputAxis& axis)
		{
			padDevice->disconnectMoveAxisAction(axis);
		}
	}
}
