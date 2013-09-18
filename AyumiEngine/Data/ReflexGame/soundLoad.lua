-- Sound resource load script
-- Szymon "Veldrin" Jab�o�ski
-- 30.08.2011

-- sound data

pitch = 1.0
volume = 60
isLooped = false

-- communication with Engine

SoundManager:addMusicTrack("IntroTrack","Data/Sound/introMusic.ogg",pitch,volume,isLooped)
SoundManager:addSoundEffect("M16","Data/Sound/m16.wav",pitch,volume,isLooped)
