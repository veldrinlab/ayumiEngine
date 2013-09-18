/**
 * File contains declaraion of SoundManager class.
 * @file    SoundManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-27
 */

#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <vector>

#include "SoundEffect.hpp"
#include "MusicTrack.hpp"

#include "../AyumiScript.hpp"
#include "../AyumiCore/Configuration.hpp"
#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiSound
	{
		typedef std::vector<MusicTrack*> SoundTrack;
		typedef std::vector<SoundEffect*> SoundEffects;

		/**
		 * Class represents one of main Engine modules which is used to store and update static and 3D sound
		 * effects and music tracks. All audio data are loaded from sound script or directly from user game source
		 * code. 
		 */
		class SoundManager
		{
		private:
			AyumiScript* soundScript;
			SoundTrack soundTrack;
			SoundEffects soundEffects;
			AyumiMath::Vector3D listenerPosition;

			void prepareSoundScript();
			void addSoundEffect(const std::string& name, const std::string& path, const float pitch, const float volume,const bool isLooped);
			void addMusicTrack(const std::string& name, const std::string& path, const float pitch, const float volume,const bool isLooped);
			void add3DSoundEffect(const std::string& name, const std::string& path, const float pitch, const float volume,const bool isLooped, const luabind::object& position);
			void add3DMusicTrack(const std::string& name, const std::string& path, const float pitch, const float volume,const bool isLooped, const luabind::object& position);
			void deleteSoundEffect(const std::string& name);
			void deleteMusicTrack(const std::string& name);
			void clearSoundEffects();
			void clearMusicTracks();

		public:
			SoundManager();
			~SoundManager();

			void initializeSoundManager();
			void updateSounds(const std::string& scriptPath);
			void updateListenerPosition(const AyumiMath::Vector3D& position);
			void update3DSoundEffect(const std::string& name, const AyumiMath::Vector3D& position);
			void update3DMusicTrack(const std::string& name, const AyumiMath::Vector3D& position);
			void playSoundEffect(const std::string& name);
			void playMusicTrack(const std::string& name);
			void pauseSoundEffect(const std::string& name);
			void pauseMusicTrack(const std::string& name);
			void stopSoundEffect(const std::string& name);
			void stopMusicTrack(const std::string& name);
		};
	}
}
#endif
