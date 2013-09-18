/**
 * File contains definition of Keyboard class.
 * @file    Keyboard.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#include "Keyboard.hpp"

namespace AyumiEngine
{
	namespace AyumiInput
	{
		/**
		 * Class default constructor. Create empty object, ready to initialize.
		 */
		Keyboard::Keyboard()
		{
			keyMap = new KeyboardInput();
		}

		/**
		 * Class destructor, clear allocated memory by clear std::map.
		 */
		Keyboard::~Keyboard()
		{
			for(KeyboardInput::const_iterator it = keyMap->begin(); it != keyMap->end(); ++it)
				delete (*it).second;
			delete keyMap;
		}

		/**
		 * InputKey enumeration incrementation operator.
		 * @param	keyEnum is InputKey value.
		 * @return	next enum value.
		 */
		InputKey& operator++(InputKey &keyEnum)
		{
			keyEnum = static_cast<InputKey>(keyEnum + 1);
			return keyEnum;
		}

		/**
		 * Method is used to initialize device. All Keyboard signlas are connected with null action slot.
		 */
		void Keyboard::initializeDevice()
		{
			for(InputKey key = A; key <= Z; ++key)
			{
				keyMap->insert(std::pair<InputKey,InputAction*>(key,new InputAction()));
				keyMap->at(key)->signal.connect(boost::bind(&Keyboard::nullAction,this));
			}

			for(InputKey key = Num0; key <= Num9; ++key)
			{
				keyMap->insert(std::pair<InputKey,InputAction*>(key,new InputAction()));
				keyMap->at(key)->signal.connect(boost::bind(&Keyboard::nullAction,this));
			}

			for(InputKey key = Escape; key <= Pause; ++key)
			{
				keyMap->insert(std::pair<InputKey,InputAction*>(key,new InputAction()));
				keyMap->at(key)->signal.connect(boost::bind(&Keyboard::nullAction,this));
			}
		}

		/**
		 * Method is used to connect device signal with user defined slot function.
		 * @param	key is id of device signal, one of InputKey enumeration.
		 * @param	method is pointer to user defined slot, class method or function.
		 */
		void Keyboard::connectAction(const InputKey& key,boost::function<void ()> method)
		{
			keyMap->at(key)->signal.connect(method);
		}

		/**
		 * Method is used to disconnect device signal with all connected slots.
		 * @param	key is id of device signal, one of InputKey enumeration.
		 */
		void Keyboard::disconnectAction(const InputKey& key)
		{
			keyMap->at(key)->signal.disconnect_all_slots();
			keyMap->at(key)->signal.connect(boost::bind(&Keyboard::nullAction,this));
		}

		/** 
		 * Accesor to class keyMap private member.
		 * @return	pointer to keyMap structure.
		 */
		KeyboardInput* Keyboard::getKeyMap() const
		{
			return keyMap;
		}
	}
}
