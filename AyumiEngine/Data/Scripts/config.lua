-- Configuration script
-- Szymon "Veldrin" Jab³oñski
-- 10.07.2011

-- configuration data

resolutionWidth = 800
resolutionHeight = 480	
colorDepth = 32
msaaLevel = 4
fullscreenEnabled = false
vSyncEnabled = false
windowCaption = "Ayumi Engine Demo"

textureScriptName = "Data/Scripts/textureLoad.lua"
meshScriptName = "Data/Scripts/meshLoad.lua"
shaderScriptName = "Data/Scripts/shaderLoad.lua"
materialScriptName = "Data/Scripts/materialLoad.lua"
lightScriptName = "Data/Scripts/lightLoad.lua"
soundScriptName = "Data/Scripts/soundLoad.lua"
effectScriptName = "Data/Scripts/effectLoad.lua"

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