/**
 * File contains declaraion of SoundManager class.
 * @file    SoundManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-27
 */

#include "SoundManager.hpp"

using namespace std;
using namespace AyumiEngine::AyumiCore;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiSound
	{
		/**
		 * Class default constructor. Create and prepeare sound loading script.
		 */
		SoundManager::SoundManager()
		{
			soundScript = new AyumiScript(Configuration::getInstance()->getSoundScriptName()->c_str());
			prepareSoundScript();
			listenerPosition.set(0.0f,0.0f,0.0f);
		}

		/**
		 * Class destructor, free allocated memory. Clear audio collections.
		 */
		SoundManager::~SoundManager()
		{
			for(SoundTrack::const_iterator it = soundTrack.begin(); it != soundTrack.end(); ++it)
				delete (*it);
			for(SoundEffects::const_iterator it = soundEffects.begin(); it != soundEffects.end(); ++it)
				delete (*it);
			delete soundScript;
		}

		/**
		 * Method is used to initialize sound manager. Execute sound loading script.
		 */
		void SoundManager::initializeSoundManager()
		{
			soundScript->executeScript();
		}

		/**
		 * Method is used to update sounds collection by running resource control Lua script.
		 * @param	scriptPath is path to Lua resource control script.
		 */
		void SoundManager::updateSounds(const string& scriptPath)
		{
			soundScript->setScriptFile(scriptPath.c_str());
			soundScript->executeScript();
		}

		/**
		 * Method is used to update sound listener position.
		 */
		void SoundManager::updateListenerPosition(const Vector3D& position)
		{
			sf::Listener::setPosition(position[0],position[1],position[2]);
		}

		/**
		 * Method is used to update 3D sound effects position.
		 * @param	name is sound effect id.
		 * @param	position is new sound effect position.
		 */
		void SoundManager::update3DSoundEffect(const string& name, const Vector3D& position)
		{
			vector<SoundEffect*>::const_iterator begin = soundEffects.begin();
			vector<SoundEffect*>::const_iterator end = soundEffects.end();

			for(; begin != end; ++begin)
				if((*begin)->getSoundName() == name)
					(*begin)->initialize3DSoundEffect(position);
		}

		/**
		 * Method is used to update 3D music track position.
		 * @param	name is music track id.
		 * @param	position is new music track position.
		 */
		void SoundManager::update3DMusicTrack(const string& name, const Vector3D& position)
		{
			vector<MusicTrack*>::const_iterator begin = soundTrack.begin();
			vector<MusicTrack*>::const_iterator end = soundTrack.end();

			for(; begin != end; ++begin)
				if((*begin)->getSoundName() == name)
					(*begin)->initialize3DMusicTrack(position);
		}

		/**
		 * Method is used to start playing sound effect.
		 * @param	name is sound effect name.
		 */
		void SoundManager::playSoundEffect(const string& name)
		{
			vector<SoundEffect*>::const_iterator begin = soundEffects.begin();
			vector<SoundEffect*>::const_iterator end = soundEffects.end();

			for(; begin != end; ++begin)
				if((*begin)->getSoundName() == name)
					(*begin)->playSoundEffect();
		}

		/**
		 * Method is used to start playing muisc track.
		 * @param	name is music track name.
		 */
		void SoundManager::playMusicTrack(const string& name)
		{
			vector<MusicTrack*>::const_iterator begin = soundTrack.begin();
			vector<MusicTrack*>::const_iterator end = soundTrack.end();

			for(; begin != end; ++begin)
				if((*begin)->getSoundName() == name)
					(*begin)->playMusicTrack();
		}

		/**
		 * Method is used to pause playing sound effect.
		 * @param	name is sound effect name.
		 */
		void SoundManager::pauseSoundEffect(const string& name)
		{
			vector<SoundEffect*>::const_iterator begin = soundEffects.begin();
			vector<SoundEffect*>::const_iterator end = soundEffects.end();

			for(; begin != end; ++begin)
				if((*begin)->getSoundName() == name)
					(*begin)->pauseSoundEffect();
		}

		/**
		 * Method is used to pause playing music track.
		 * @param	name is muisc track name.
		 */
		void SoundManager::pauseMusicTrack(const string& name)
		{
			vector<MusicTrack*>::const_iterator begin = soundTrack.begin();
			vector<MusicTrack*>::const_iterator end = soundTrack.end();

			for(; begin != end; ++begin)
				if((*begin)->getSoundName() == name)
					(*begin)->pauseMusicTrack();
		}

		/**
		 * Method is used to stop playing sound effect.
		 * @param	name is sound effect name.
		 */
		void SoundManager::stopSoundEffect(const string& name)
		{
			vector<SoundEffect*>::const_iterator begin = soundEffects.begin();
			vector<SoundEffect*>::const_iterator end = soundEffects.end();

			for(; begin != end; ++begin)
				if((*begin)->getSoundName() == name)
					(*begin)->stopSoundEffect();
		}

		/**
		 * Method is used to stop playing music track.
		 * @param	name is music track name.
		 */ 
		void SoundManager::stopMusicTrack(const string& name)
		{
			vector<MusicTrack*>::const_iterator begin = soundTrack.begin();
			vector<MusicTrack*>::const_iterator end = soundTrack.end();

			for(; begin != end; ++begin)
				if((*begin)->getSoundName() == name)
					(*begin)->stopMusicTrack();
		}

		/**
		 * Private method which is used to prepare loading script. By using Luabind engine register Manager class
		 * to Lua namespace and bind global pointer to manager object.
		 */
		void SoundManager::prepareSoundScript()
		{
			luabind::module(soundScript->getVirtualMachine())
			[
				luabind::class_<SoundManager>("SoundManager")
				.def("addSoundEffect",&SoundManager::addSoundEffect)
				.def("addMusicTrack", &SoundManager::addMusicTrack)
				.def("add3DSoundEffect",&SoundManager::add3DSoundEffect)
				.def("add3DMusicTrack", &SoundManager::add3DMusicTrack)
				.def("deleteSoundffect",&SoundManager::deleteSoundEffect)
				.def("deleteMusicTrack",&SoundManager::deleteMusicTrack)
				.def("clearSoundEffects",&SoundManager::clearSoundEffects)
				.def("clearMusicTracks",&SoundManager::deleteSoundEffect)
			];
			luabind::globals(soundScript->getVirtualMachine())["SoundManager"] = this;
		}

		/**
		 * Method is used to add new sound effect. It can be called from Lua script.
		 * @param	name is sound name.
		 * @param	path is sound file path.
		 * @param	pitch is sound pitch.
		 * @param	volume is sound volume.
		 * @param	isLooped is sound loop flag.
		 */
		void SoundManager::addSoundEffect(const string& name,const string& path, const float pitch, const float volume, const bool isLooped)
		{
			SoundEffect* sound = new SoundEffect(name,path);
			sound->initializeSoundEffect(pitch,volume,isLooped);
			soundEffects.push_back(sound);
		}

		/**
		 * Method is used to add new music track from. It can be called from Lua script.
		 * @param	name is sound name.
		 * @param	path is sound file path.
		 * @param	pitch is sound pitch.
		 * @param	volume is sound volume.
		 * @param	isLooped is sound loop flag.
		 */
		void SoundManager::addMusicTrack(const string& name, const string& path, const float pitch, const float volume, const bool isLooped)
		{
			MusicTrack* music = new MusicTrack(name,path);
			music->initializeMusicTrack(pitch,volume,isLooped);
			soundTrack.push_back(music);
		}

		/**
		 * Method is used to add new 3D sound effect. It can be called from Lua script.
		 * @param	name is sound name.
		 * @param	path is sound file path.
		 * @param	pitch is sound pitch.
		 * @param	volume is sound volume.
		 * @param	isLooped is sound loop flag.
		 * @param	position is 3d sound position.
		 */
		void SoundManager::add3DSoundEffect(const string& name, const string& path, const float pitch, const float volume, const bool isLooped, const luabind::object& position)
		{
			SoundEffect* sound = new SoundEffect(name,path);
			sound->initializeSoundEffect(pitch,volume,isLooped);
			sound->initialize3DSoundEffect(Vector3D(luabind::object_cast<float>(position[1]),luabind::object_cast<float>(position[2]),luabind::object_cast<float>(position[3])));
			soundEffects.push_back(sound);
		}

		/**
		 * Method is used to add new music track from Lua script.
		 * @param	name is sound name.
		 * @param	path is sound file path.
		 * @param	pitch is sound pitch.
		 * @param	volume is sound volume.
		 * @param	isLooped is sound loop flag.
		 * @param	position is 3d sound position.
		 */
		void SoundManager::add3DMusicTrack(const string& name, const string& path, const float pitch, const float volume, const bool isLooped, const luabind::object& position)
		{
			MusicTrack* music = new MusicTrack(name,path);
			music->initializeMusicTrack(pitch,volume,isLooped);
			music->initialize3DMusicTrack(Vector3D(luabind::object_cast<float>(position[1]),luabind::object_cast<float>(position[2]),luabind::object_cast<float>(position[3])));
			soundTrack.push_back(music);
		}
		
		/**
		 * Method is used to delete sound effect from colletion. It can be called from Lua script.
		 * @param	name is sound effect id.
		 */
		void SoundManager::deleteSoundEffect(const string& name)
		{
			vector<SoundEffect*>::const_iterator begin = soundEffects.begin();
			vector<SoundEffect*>::const_iterator end = soundEffects.end();

			for(; begin != end; ++begin)
				if((*begin)->getSoundName() == name)
					break;
			if(begin != end)
				soundEffects.erase(begin);
		}

		/**
		 * Method is used to delete music track from colletion. It can be called from Lua script.
		 * @param	name is music track id.
		 */
		void SoundManager::deleteMusicTrack(const string& name)
		{
			vector<MusicTrack*>::const_iterator begin = soundTrack.begin();
			vector<MusicTrack*>::const_iterator end = soundTrack.end();

			for(; begin != end; ++begin)
				if((*begin)->getSoundName() == name)
					break;
			if(begin != end)
				soundTrack.erase(begin);
		}
		
		/**
		 * Method is used to delete all sound effects. It cane be called from Lua script.
		 */
		void SoundManager::clearSoundEffects()
		{
			soundEffects.clear();
		}
		
		/**
		 * Method is used to delete all music tracks. It can be called from Lua script.
		 */
		void SoundManager::clearMusicTracks()
		{
			 soundTrack.clear();
		}
	}
}
