-- Effect script - Depth of Field
-- Szymon "Veldrin" Jab³oñski
-- 21.11.2011

--effect data
effectName = "DepthOfField"
renderPassAmount = 3

-- first pass data
renderTarget = "ColorBuffer"
textureType = "Rectangle"
renderTargetWidth = 800
renderTargetHeight = 600

-- params
focalDistance = 4.5
focalRange = 20.0

-- communication with Engine

-- create first pass
-- Simple off-screen rendering

Effect:startEffectPass()
Effect:loadFrameBufferParams(renderTarget,renderTargetWidth,renderTargetHeight,textureType)
Effect:loadEffectShader("DepthOfFieldFXPass1")
Effect:loadOffScreenRenderingScene(true)
Effect:loadOffScreenRenderingPrevious(false)
Effect:loadFinalRendering(false)
Effect:loadClearBeforeFinal(false)
Effect:loadEffectFloatUniform("focalDistance",focalDistance)
Effect:loadEffectFloatUniform("focalRange",focalRange)
Effect:endEffectPass()


-- create second pass
Effect:startEffectPass()
Effect:loadFrameBufferParams(renderTarget,renderTargetWidth,renderTargetHeight,textureType)
Effect:loadEffectShader("DepthOfFieldFXPass2")
Effect:loadOffScreenRenderingScene(false)
Effect:loadOffScreenRenderingPrevious(true)
Effect:loadFinalRendering(false)
Effect:loadClearBeforeFinal(false)
Effect:endEffectPass()

-- render result, final pass
Effect:startEffectPass()
Effect:loadFrameBufferParams(renderTarget,renderTargetWidth,renderTargetHeight,textureType)
Effect:loadEffectShader("DepthOfFieldFXPass3")
Effect:loadOffScreenRenderingScene(false)
Effect:loadOffScreenRenderingPrevious(false)
Effect:loadFinalRendering(true)
Effect:loadClearBeforeFinal(true)
Effect:endEffectPass()
