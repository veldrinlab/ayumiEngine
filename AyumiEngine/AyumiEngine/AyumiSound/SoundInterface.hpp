/**
 * File contains declaraion of SoundInterface class.
 * @file    SoundInterface.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-27
 */

#ifndef SOUNDINTERFACE_HPP
#define SOUNDINTERFACE_HPP

#include <string>

namespace AyumiEngine
{
	namespace AyumiSound
	{
		/**
		 * Class represents very simple interface for storing and controlling sound data. Such data like name,
		 * path, volume or loop flag which is same for any kind of sound classes.
		 */
		class SoundInterface
		{
		protected:
			std::string soundName;
			std::string soundPath;
			float pitch;
			float volume;
			bool isLooped;

		public:			

			/**
			 * Class destructor, free allocated memory. Nothing to delete.
			 */
			virtual ~SoundInterface() {};

			void increaseVolume();
			void decreaseVolume();
			std::string getSoundName() const;		
			void setLoop(const bool isLooped);
		};
	}
}
#endif
