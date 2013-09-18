-- Configuration script
-- Szymon "Veldrin" Jab³oñski
-- 10.07.2011

-- configuration data

resolutionWidth = 800
resolutionHeight = 600	
colorDepth = 32
msaaLevel = 8
fullscreenEnabled = false
vSyncEnabled = false
windowCaption = "Ayumi Engine Demo"

textureScriptName = "Data/ReflexGame/textureLoad.lua"
meshScriptName = "Data/ReflexGame/meshLoad.lua"
shaderScriptName = "Data/ReflexGame/shaderLoad.lua"
materialScriptName = "Data/ReflexGame/materialLoad.lua"
lightScriptName = "Data/ReflexGame/lightLoad.lua"
soundScriptName = "Data/ReflexGame/soundLoad.lua"
effectScriptName = "Data/ReflexGame/effectLoad.lua"

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