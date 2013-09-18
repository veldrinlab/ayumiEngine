/**
 * File contains definition of Mouse class.
 * @file    Mouse.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-13
 */

#include "Mouse.hpp"

namespace AyumiEngine
{
	namespace AyumiInput
	{
		/**
		 * Class default constructor. Create empty object, ready to initialize.
		 */
		Mouse::Mouse()
		{
			buttonMap = new MouseInput();
			mouseMoveSignal = new InputMoveAction();
			mouseWheelMoveSignal = new InputMoveWheelAction();
		}

		/**
		 * Class destructor, clear allocated memory by clear std::map
		 */
		Mouse::~Mouse()
		{
			for(MouseInput::const_iterator it = buttonMap->begin(); it != buttonMap->end(); ++it)
				delete (*it).second;
			delete mouseMoveSignal;
			delete mouseWheelMoveSignal;
			delete buttonMap;
		}

		/**
		 * InputButton enumeration incrementation operator.
		 * @param	buttonEnum is InputButton value.
		 * @return	next enum value.
		 */
		InputMouseButton& operator++(InputMouseButton& buttonEnum)
		{
			buttonEnum = static_cast<InputMouseButton>(buttonEnum + 1);
			return buttonEnum;
		}

		/**
		 * Method is used to initialize device. All Mouse signlas are connected with null action slot.
		 */
		void Mouse::initializeDevice()
		{
			for(InputMouseButton button = LeftButton; button != XButton2; ++button)
			{
				buttonMap->insert(std::pair<InputMouseButton,InputAction*>(button,new InputAction()));
				buttonMap->at(button)->signal.connect(boost::bind(&Mouse::nullAction,this));
			}
			
			mouseMoveSignal->signal.connect(boost::bind(&Mouse::nullMoveAction,this,_1,_2));
			mouseWheelMoveSignal->signal.connect(boost::bind(&Mouse::nullWhellMoveAction,this,_1));
		}

		/**
		 * Method is used to connect device signal with user defined slot function.
		 * @param	button is id of device signal, one of InputButton enumeration.
		 * @param	method is pointer to user defined slot, class method or function.
		 */
		void Mouse::connectAction(const InputMouseButton& button,boost::function<void ()> method)
		{
			buttonMap->at(button)->signal.connect(method);
		}

		/**
		 * Method is used to connect device move signal with user defined slot function.
		 * @param	method is pointer to user defined slot, class method or function.
		 */
		void Mouse::connectMoveAction(boost::function<void (int,int)> method)
		{
			mouseMoveSignal->signal.connect(method);
		}

		/**
		 * Method is used to connect device wheel move signal with user defined slot function.
		 * @param	method is pointer to user defined slot, class method or function.
		 */
		void Mouse::connectMoveWheelAction(boost::function<void (int)> method)
		{
			mouseWheelMoveSignal->signal.connect(method);
		}

		/**
		 * Method is used to disconnect device signal with all connected slots and connect with
		 * null action again.
		 * @param	button is id of device signal, one of InputKey enumeration.
		 */
		void Mouse::disconnectAction(const InputMouseButton& button)
		{
			buttonMap->at(button)->signal.disconnect_all_slots();
			buttonMap->at(button)->signal.connect(boost::bind(&Mouse::nullAction,this));
		}

		/**
		 * Method is used to disconnect device move signal with all connected slots and connect with
		 * null action again.
		 */
		void Mouse::disconnectMoveAction()
		{
			mouseMoveSignal->signal.disconnect_all_slots();
			mouseMoveSignal->signal.connect(boost::bind(&Mouse::nullMoveAction,this,_1,_2));
		}

		/**
		 * Method is used to disconnect device wheel move signal with all connected slots and connect with
		 * null action again.
		 */
		void Mouse::disconnectMoveWheelAction()
		{
			mouseWheelMoveSignal->signal.disconnect_all_slots();
			mouseWheelMoveSignal->signal.connect(boost::bind(&Mouse::nullWhellMoveAction,this,_1));
		}

		/** 
		 * Accesor to class buttonMap private member.
		 * @return	pointer to buttonMap structure.
		 */
		MouseInput* Mouse::getButtonMap() const
		{
			return buttonMap;
		}

		/** 
		 * Accesor to class mouseMove private member.
		 * @return	pointer to mouseMove signal class.
		 */
		InputMoveAction* Mouse::getMouseMoveSignal() const
		{
			return mouseMoveSignal;
		}

		/** 
		 * Accesor to class mouse wheel move private member.
		 * @return	pointer to mouse wheel move signal class.
		 */
		InputMoveWheelAction* Mouse::getMouseWheelMoveSignal() const
		{
			return mouseWheelMoveSignal;
		}
	}
}
