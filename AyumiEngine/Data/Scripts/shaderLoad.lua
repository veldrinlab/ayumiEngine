-- Shader resource load script
-- Szymon "Veldrin" Jab³oñski
-- 23.04.2011

-- shader data

-- communication with Engine

-- Post process FX
--ShaderManager:registerResource("GrayscaleFX","VertexFragment","Data/Shader/grayscale.vert","Data/Shader/grayscale.frag")
--ShaderManager:registerResource("SepiaFX","VertexFragment","Data/Shader/sepia.vert","Data/Shader/sepia.frag")
--ShaderManager:registerResource("ColorInvertFX","VertexFragment","Data/Shader/colorInvert.vert","Data/Shader/colorInvert.frag")
--ShaderManager:registerResource("MotionBlurFX","VertexFragment","Data/Shader/motionBlur.vert","Data/Shader/motionBlur.frag")
--ShaderManager:registerResource("PixelationFX","VertexFragment","Data/Shader/pixelation.vert","Data/Shader/pixelation.frag")
--ShaderManager:registerResource("ThermalVisionFX","VertexFragment","Data/Shader/thermalVision.vert","Data/Shader/thermalVision.frag")
--ShaderManager:registerResource("VoidFX","VertexFragment","Data/Shader/void.vert","Data/Shader/void.frag")
--ShaderManager:registerResource("BloomFX","VertexFragment","Data/Shader/bloom.vert","Data/Shader/bloom.frag")
--ShaderManager:registerResource("BlurFX","VertexFragment","Data/Shader/blur.vert","Data/Shader/blur.frag")

--ShaderManager:registerResource("DepthOfFieldFXPass1","VertexFragment","Data/Shader/depthOfFieldPass1.vert","Data/Shader/depthOfFieldPass1.frag")
--ShaderManager:registerResource("DepthOfFieldFXPass2","VertexFragment","Data/Shader/depthOfFieldPass2.vert","Data/Shader/depthOfFieldPass2.frag")
--ShaderManager:registerResource("DepthOfFieldFXPass3","VertexFragment","Data/Shader/depthOfFieldPass3.vert","Data/Shader/depthOfFieldPass3.frag")

-- test
--ShaderManager:registerResource("GodRaysFX","VertexFragment","Data/Shader/godrays.vert","Data/Shader/godrays.frag")



-- do terrain/sky dema
ShaderManager:registerResource("Terrain","VertexFragment","Data/Shader/terrain.vert","Data/Shader/terrain.frag")
ShaderManager:registerResource("Skydome","VertexFragment","Data/Shader/skyDome.vert","Data/Shader/skyDome.frag")
ShaderManager:registerResource("Preetham","VertexFragment","Data/Shader/preetham.vert","Data/Shader/preetham.frag")


-- do wall dema
--ShaderManager:registerResource("Skybox","VertexFragment","Data/Shader/skybox.vert","Data/Shader/skybox.frag")


-- materials demo
ShaderManager:registerResource("TextureMapping","VertexFragment","Data/Shader/textureMapping.vert","Data/Shader/textureMapping.frag")
--ShaderManager:registerResource("NormalMapping","VertexFragment","Data/Shader/normalMapping.vert","Data/Shader/normalMapping.frag")
--ShaderManager:registerResource("ParallaxMapping","VertexFragment","Data/Shader/parallaxMapping.vert","Data/Shader/parallaxMapping.frag")
--ShaderManager:registerResource("CubeMapping","VertexFragment","Data/Shader/cubeMapping.vert","Data/Shader/cubeMapping.frag")
--ShaderManager:registerResource("SphereMapping","VertexFragment","Data/Shader/sphereMapping.vert","Data/Shader/sphereMapping.frag")
--ShaderManager:registerResource("EnvironmentMapping","VertexFragment","Data/Shader/environmentMapping.vert","Data/Shader/environmentMapping.frag")
--ShaderManager:registerResource("CellShading","VertexFragment","Data/Shader/cellShading.vert","Data/Shader/cellShading.frag")
--ShaderManager:registerResource("Billboarding","VertexFragment","Data/Shader/billboarding.vert","Data/Shader/billboarding.frag")


-- do particle demo
--ShaderManager:registerResource("SmokeParticles","VertexGeometryFragment","Data/Shader/smokeParticles.vert","Data/Shader/smokeParticles.frag","Data/Shader/smokeParticles.geom")


-- shadow mapping demo
--ShaderManager:registerResource("ShadowMapping","VertexFragment","Data/Shader/shadowMapping.vert","Data/Shader/shadowMapping.frag")
--ShaderManager:registerResource("SoftShadowMapping","VertexFragment","Data/Shader/softShadowMapping.vert","Data/Shader/softShadowMapping.frag")

-- animation demo
--ShaderManager:registerResource("Animation","VertexFragment","Data/Shader/animation.vert","Data/Shader/animation.frag")



 -- additional
--ShaderManager:registerResource("DayAndNight","VertexFragment","Data/Shader/dayAndNight.vert","Data/Shader/dayAndNight.frag")








