/**
 * File contains declaraion of SoundEffect class.
 * @file    SoundEffect.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-27
 */

#ifndef SOUNDEFFECT_HPP
#define SOUNDEFFECT_HPP

#include <SFML/Audio.hpp>

#include "SoundInterface.hpp"
#include "../Logger.hpp"
#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiSound
	{
		/**
		 * Class represents one of possible sound type: SoundEffect which is used to play short sound effects
		 * like explosions, bumps, roars etc. SoundEffect can be initialized like a static sound or 3D sound.
		 * Warning: mp3 file are not supported. It is suggested to use *wav format for sound effects.
		 */
		class SoundEffect : public SoundInterface
		{
		private:
			sf::SoundBuffer effectBuffer;
			sf::Sound effectSound;
		public:
			SoundEffect(const std::string& name, const std::string& path);
			~SoundEffect();

			void initializeSoundEffect(const float pitch, const float volume, const bool isLooped);
			void initialize3DSoundEffect(const AyumiMath::Vector3D& position);
			void playSoundEffect();
			void pauseSoundEffect();
			void stopSoundEffect();
		};
	}
}
#endif
