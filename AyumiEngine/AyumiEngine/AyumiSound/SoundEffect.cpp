/**
 * File contains definition of SoundEffect class.
 * @file    SoundEffect.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-27
 */

#include "SoundEffect.hpp"

using namespace std;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiSound
	{
		/**
		 * Class constructor with initialize parametres. Set basic data and load sound from file.
		 * @param	name is sound effect name.
		 * @param	path is sound effect file path.
		 */
		SoundEffect::SoundEffect(const string& name, const string& path)
		{
			soundName = name;
			soundPath = path;

			if(!effectBuffer.loadFromFile(path))
			{
				Logger::getInstance()->saveLog(Log<string>("Error loading sound effect: "));
				Logger::getInstance()->saveLog(Log<string>(name));
			}
		}

		/**
		 * Class destructor, free allocated memeory. Nothind to delete.
		 */
		SoundEffect::~SoundEffect()
		{
			
		}

		/**
		 * Method is used to initiaize soudn effect parameters.
		 * @param	pitch is sound pith.
		 * @param	volume is sound volume.
		 * @param	isLooped is sound loop flag.
		 */
		void SoundEffect::initializeSoundEffect(const float pitch, const float volume, const bool isLooped)
		{
			this->pitch = pitch;
			this->volume = volume;
			this->isLooped = isLooped;

			effectSound.setBuffer(effectBuffer);
			effectSound.setLoop(isLooped);
			effectSound.setPitch(pitch);
			effectSound.setVolume(volume);
		}

		/**
		 * Method is used to initialize 3D sound effect.
		 * @param	position is 3D sound position.
		 */
		void SoundEffect::initialize3DSoundEffect(const Vector3D& position)
		{
			effectSound.setPosition(position.x(),position.y(),position.z());
			effectSound.setRelativeToListener(true);
		}

		/**
		 * Method is used to start playing sound effect.
		 */
		void SoundEffect::playSoundEffect()
		{
			effectSound.play();
		}

		/**
		 * Method is used to pause playing sound effect.
		 */
		void SoundEffect::pauseSoundEffect()
		{
			effectSound.pause();
		}

		/**
		 * Method is used to stop playing sound effect.
		 */
		void SoundEffect::stopSoundEffect()
		{
			effectSound.stop();
		}
	}
}
