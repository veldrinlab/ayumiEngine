-- Sound resource load script
-- Szymon "Veldrin" Jab³oñski
-- 30.08.2011

-- sound data

pitch = 1.0
volume = 60
isLooped = false

-- communication with Engine


SoundManager:addSoundEffect("Explosion","Data/Sound/explosion.wav",pitch,volume,isLooped)
SoundManager:addSoundEffect("Laser","Data/Sound/laser.wav",pitch,volume,isLooped)
SoundManager:addSoundEffect("M16","Data/Sound/m16.wav",pitch,volume,isLooped)
