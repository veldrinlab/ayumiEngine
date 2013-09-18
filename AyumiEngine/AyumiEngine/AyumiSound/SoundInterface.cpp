/**
 * File contains definition of SoundInterface class.
 * @file    SoundInterface.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-27
 */

#include "SoundInterface.hpp"

using namespace std;

namespace AyumiEngine
{
	namespace AyumiSound
	{
		/**
		 * Method is used to increase sound volume.
		 */
		void SoundInterface::increaseVolume()
		{
			if(volume <= 100.0f)
				volume++;
		}

		/**
		 * Method is used to decrease sound volume.
		 */
		void SoundInterface::decreaseVolume()
		{
			if(volume > 0.0f)
				volume--;
		}

		/**
		 * Accessor to private sound name memebr.
		 * @return	sound name.
		 */
		string SoundInterface::getSoundName() const
		{
			return soundName;
		}

		/**
		 * Setter for private loop flag member.
		 * @param	isLooped is loop flag bool value.
		 */
		void SoundInterface::setLoop(const bool isLooped)
		{
			this->isLooped = isLooped;
		}
	}
}
