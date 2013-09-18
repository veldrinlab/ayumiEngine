/**
 * File contains declaraion of MusicTrack class.
 * @file    MusicTrack.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-27
 */

#ifndef MUSICTRACK_HPP
#define MUSICTRACK_HPP

#include <SFML/Audio.hpp>

#include "SoundInterface.hpp"
#include "../Logger.hpp"
#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiSound
	{
		/**
		 * Class represents one of possible sound type: MusicTrack which is used to play long music track like
		 * background soundtrack, intro/credit/menu music, dialogs etc. MusicTracks can be initialized like a static
		 * sound or 3D sound. Warning: mp3 file are not supported. It is suggested to use *ogg format for sound effects.
		 */
		class MusicTrack : public SoundInterface
		{
		private:
			sf::Music musicTrack;

		public:
			MusicTrack(const std::string& name, const std::string& path);
			~MusicTrack();

			void initializeMusicTrack(const float pitch, const float volume, const bool isLooped);
			void initialize3DMusicTrack(const AyumiMath::Vector3D& position);

			void playMusicTrack();
			void pauseMusicTrack();
			void stopMusicTrack();
		};
	}
}
#endif
