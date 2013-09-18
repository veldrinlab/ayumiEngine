/**
 * File contains definition of MusicTrack class.
 * @file    MusicTrack.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-27
 */

#include "MusicTrack.hpp"

using namespace std;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiSound
	{
		/**
		 * Class constructor with initialize parametres. Set basic data and load music from file.
		 * @param	name is music track name.
		 * @param	path is music track file path.
		 */
		MusicTrack::MusicTrack(const string& name, const string& path)
		{
			soundName = name;
			soundPath = path;

			if(!musicTrack.openFromFile(path))
			{
				Logger::getInstance()->saveLog(Log<string>("Error loading music track: "));
				Logger::getInstance()->saveLog(Log<string>(name));
			}
		}
		
		/**
		 * Class destructor, free allocated memeory. Nothind to delete.
		 */
		MusicTrack::~MusicTrack()
		{

		}
		
		/**
		 * Method is used to initiaize music track parameters.
		 * @param	pitch is sound pith.
		 * @param	volume is sound volume.
		 * @param	isLooped is sound loop flag.
		 */
		void MusicTrack::initializeMusicTrack(const float pitch, const float volume, const bool isLooped)
		{
			this->pitch = pitch;
			this->volume = volume;
			this->isLooped = isLooped;

			musicTrack.setLoop(isLooped);
			musicTrack.setPitch(pitch);
			musicTrack.setVolume(volume);
			musicTrack.setPosition(0.0f,0.0f,0.0f);
			musicTrack.setRelativeToListener(false);
		}

		/**
		 * Method is used to initialize 3D music track.
		 * @param	position is 3D sound position.
		 */
		void MusicTrack::initialize3DMusicTrack(const Vector3D& position)
		{
			musicTrack.setPosition(position.x(),position.y(),position.z());
			musicTrack.setRelativeToListener(true);
		}

		/**
		 * Method is used to start playing music track.
		 */
		void MusicTrack::playMusicTrack()
		{
			musicTrack.play();
		}

		/**
		 * Method is used to pause playing music track.
		 */
		void MusicTrack::pauseMusicTrack()
		{
			musicTrack.pause();
		}

		/**
		 * Method is used to stop playing music track.
		 */
		void MusicTrack::stopMusicTrack()
		{
			musicTrack.stop();
		}
	}
}
