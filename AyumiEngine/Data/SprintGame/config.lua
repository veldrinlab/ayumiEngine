-- Configuration script
-- Szymon "Veldrin" Jab³oñski
-- 10.07.2011

-- configuration data

resolutionWidth = 800
resolutionHeight = 480
colorDepth = 32
msaaLevel = 8
fullscreenEnabled = false
vSyncEnabled = false
windowCaption = "Ayumi Engine Demo"

textureScriptName = "Data/SprintGame/textureLoad.lua"
meshScriptName = "Data/SprintGame/meshLoad.lua"
shaderScriptName = "Data/SprintGame/shaderLoad.lua"
materialScriptName = "Data/SprintGame/materialLoad.lua"
lightScriptName = "Data/SprintGame/lightLoad.lua"
soundScriptName = "Data/SprintGame/soundLoad.lua"
effectScriptName = "Data/SprintGame/effectLoad.lua"

-- communication with Engine

Config:setResolutionWidth(resolutionWidth)
Config:setResolutionHeight(resolutionHeight)
Config:setColorDepth(colorDepth)
Config:setMSAALevel(msaaLevel)
Config:setFullscreenEnabled(fullscreenEnabled)
Config:setVSyncEnabled(vSyncEnabled)
Config:setWindowCaption(windowCaption)
Config:setTextureScriptName(textureScriptName)
Config:setMeshScriptName(meshScriptName)
Config:setShaderScriptName(shaderScriptName)
Config:setMaterialScriptName(materialScriptName)
Config:setLightScriptName(lightScriptName)
Config:setSoundScriptName(soundScriptName)
Config:setEffectScriptName(effectScriptName)