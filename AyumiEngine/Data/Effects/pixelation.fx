-- Effect script - Pixelation
-- Szymon "Veldrin" Jab³oñski
-- 07.10.2011

-- effect data

effectName = "Pixelation"

frameBufferAmount = 2
renderTarget = "ColorBuffer"
textureType = "Rectangle"
renderTargetWidth = 800
renderTargetHeight = 600
shaderName = "PixelationFX"

-- params
dxName = "dx"
dx = 10.0
dyName = "dy"
dy = 10.0

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
Effect:loadEffectFloatUniform(dxName,dx)
Effect:loadEffectFloatUniform(dyName,dy)
Effect:endEffectPass()
