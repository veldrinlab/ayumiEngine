/**
 * File contains definition of GamePad class.
 * @file    GamePad.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-13
 */

#include "GamePad.hpp"

namespace AyumiEngine
{
	namespace AyumiInput
	{
		/**
		 * Class default constructor. Create empty object, ready to initialize.
		 */
		GamePad::GamePad()
		{
			axisMap = new PadAxisInput();
			buttonMap = new PadButtonInput();
		}

		/**
		 * Class destructor, free allocated memory - clear signals and delete maps.
		 */
		GamePad::~GamePad()
		{
			for(PadAxisInput::const_iterator it = axisMap->begin(); it != axisMap->end(); ++it)
				delete (*it).second;
			for(PadButtonInput::const_iterator it = buttonMap->begin(); it != buttonMap->end(); ++it)
				delete (*it).second;
			delete axisMap;
			delete buttonMap;
		}

		/**
		 * InputPadButton enumeration incrementation operator.
		 * @param	buttonEnum is InputPadButton value.
		 * @return	next enum value.
		 */
		InputPadButton& operator++(InputPadButton& buttonEnum)
		{
			buttonEnum = static_cast<InputPadButton>(buttonEnum + 1);
			return buttonEnum;
		}

		/**
		 * InputAxis enumeration incrementation operator.
		 * @param	axisEnum is InputAxis value.
		 * @return	next enum value.
		 */
		InputAxis& operator++(InputAxis& axisEnum)
		{
			axisEnum = static_cast<InputAxis>(axisEnum + 1);
			return axisEnum;
		}

		/**
		 * Method is used to initialize device. All GamePad signlas are connected with null action slot.
		 */
		void GamePad::initializeDevice()
		{
			for(InputPadButton button = Button0; button != Button31; ++button)
			{
				buttonMap->insert(std::pair<InputPadButton,InputAction*>(button, new InputAction()));
				buttonMap->at(button)->signal.connect(boost::bind(&GamePad::nullAction,this));
			}

			for(InputAxis axis = AxisX; axis != AxisPOV; ++axis)
			{
				axisMap->insert(std::pair<InputAxis,InputAxisAction*>(axis, new InputAxisAction()));
				axisMap->at(axis)->signal.connect(boost::bind(&GamePad::nullAxisMoveAction,this,_1));
			}	
		}

		/**
		 * Method is used to connect device signal with user defined slot function.
		 * @param	button is id of device signal, one of InputPadButton enumeration.
		 * @param	method is pointer to user defined slot, class method or function.
		 */
		void GamePad::connectAction(const InputPadButton& button,boost::function<void ()> method)
		{
			buttonMap->at(button)->signal.connect(method);
		}

		/**
		 * Method is used to connect defined device axis move signal with user defined slot function.
		 * @param	axis is id of device signal, one of InputAxis enumeration.
		 * @param	method is pointer to user defined slot, class method or function.
		 */
		void GamePad::connectMoveAxisAction(const InputAxis& axis, boost::function<void (float)> method)
		{
			axisMap->at(axis)->signal.connect(method);
		}

		/**
		 * Method is used to disconnect device signal with all connected slots and connect with
		 * null action again.
		 * @param	button is id of device signal, one of InputPadButton enumeration.
		 */
		void GamePad::disconnectAction(const InputPadButton& button)
		{
			buttonMap->at(button)->signal.disconnect_all_slots();
			buttonMap->at(button)->signal.connect(boost::bind(&GamePad::nullAction,this));
		}

		/**
		 * Method is used to disconnect device signal with all connected slots and connect with
		 * null action again.
		 * @param	axis is id of device signal, one of InputAxis enumeration.
		 */
		void GamePad::disconnectMoveAxisAction(const InputAxis& axis)
		{
			axisMap->at(axis)->signal.disconnect_all_slots();
			axisMap->at(axis)->signal.connect(boost::bind(&GamePad::nullAxisMoveAction,this,_1));
		}

		/** 
		 * Accesor to class axisMap private member.
		 * @return	pointer to axisMap.
		 */
		PadAxisInput* GamePad::getAxisMap() const
		{
			return axisMap;
		}

		/** 
		 * Accesor to class buttonMap private member.
		 * @return	pointer to buttonMap.
		 */
		PadButtonInput* GamePad::getButtonMap() const
		{
			return buttonMap;
		}
	}
}
