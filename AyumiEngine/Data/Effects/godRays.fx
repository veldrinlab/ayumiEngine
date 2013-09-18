-- Effect script - Blur
-- Szymon "Veldrin" Jab³oñski
-- 21.11.2011

-- effect data

effectName = "GodRays"

frameBufferAmount = 1
renderTarget = "ColorBuffer"
textureType = "Rectangle"
renderTargetWidth = 800
renderTargetHeight = 600
shaderName = "GodRaysFX"

-- params
exposureName = "exposure"
decayName = "decay"
densityName = "density"
weightName = "weight"
lightPositionOnScreenXName = "lightPositionOnScreenX"
lightPositionOnScreenYName = "lightPositionOnScreenY"
exposure = 0.0034
decay = 1.0
density = 0.84
weight = 5.65
lightPositionOnScreenX = 400
lightPositionOnScreenY = 400

-- create first pass
-- Simple off-screen rendering

Effect:startEffectPass()
Effect:loadFrameBufferParams(renderTarget,renderTargetWidth,renderTargetHeight,textureType)
Effect:loadEffectShader(shaderName)
Effect:loadOffScreenRenderingScene(true)
Effect:loadOffScreenRenderingPrevious(false)
Effect:loadFinalRendering(false)
Effect:loadClearBeforeFinal(false)
Effect:endEffectPass()

-- render result, final pass
Effect:startEffectPass()
Effect:loadFrameBufferParams(renderTarget,renderTargetWidth,renderTargetHeight,textureType)
Effect:loadEffectShader(shaderName)
Effect:loadOffScreenRenderingScene(false)
Effect:loadOffScreenRenderingPrevious(false)
Effect:loadFinalRendering(true)
Effect:loadClearBeforeFinal(true)

Effect:loadEffectFloatUniform(exposureName,exposure)
Effect:loadEffectFloatUniform(decayName,decay)
Effect:loadEffectFloatUniform(densityName,density)
Effect:loadEffectFloatUniform(weightName,weight)
Effect:loadEffectFloatUniform(lightPositionOnScreenXName,lightPositionOnScreenX)
Effect:loadEffectFloatUniform(lightPositionOnScreenYName,lightPositionOnScreenY)
Effect:endEffectPass()
