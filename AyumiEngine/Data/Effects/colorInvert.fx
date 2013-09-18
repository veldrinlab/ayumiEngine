-- Effect script - Color Invert
-- Szymon "Veldrin" Jab³oñski
-- 08.10.2011

-- effect data

effectName = "ColorInvert"

frameBufferAmount = 2
renderTarget = "ColorBuffer"
textureType = "Rectangle"
renderTargetWidth = 800
renderTargetHeight = 600
shaderName = "ColorInvertFX"

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
Effect:endEffectPass()