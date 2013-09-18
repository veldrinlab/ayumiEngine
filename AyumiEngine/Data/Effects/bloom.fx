-- Effect script - Bloom/Fake HDR
-- Szymon "Veldrin" Jab³oñski
-- 07.10.2011

-- effect data

effectName = "Bloom"

frameBufferAmount = 1
renderTarget = "ColorBuffer"
textureType = "Rectangle"
renderTargetWidth = 800
renderTargetHeight = 600
shaderName = "BloomFX"

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
