-- Shader resource load script
-- Szymon "Veldrin" Jab³oñski
-- 23.04.2011

-- shader data

-- communication with Engine

-- Drag Race game
ShaderManager:registerResource("MotionBloomFX","VertexFragment","Data/Shader/motionBloom.vert","Data/Shader/motionBloom.frag")


ShaderManager:registerResource("MotionBlurFX","VertexFragment","Data/Shader/motionBlur.vert","Data/Shader/motionBlur.frag")
ShaderManager:registerResource("BloomFX","VertexFragment","Data/Shader/bloom.vert","Data/Shader/bloom.frag")

ShaderManager:registerResource("Terrain","VertexFragment","Data/Shader/terrain.vert","Data/Shader/terrain.frag")
ShaderManager:registerResource("Skydome","VertexFragment","Data/Shader/skyDome.vert","Data/Shader/skyDome.frag")

ShaderManager:registerResource("TextureMapping","VertexFragment","Data/Shader/textureMapping.vert","Data/Shader/textureMapping.frag")
ShaderManager:registerResource("ShadowMapping","VertexFragment","Data/Shader/shadowMapping.vert","Data/Shader/shadowMapping.frag")

ShaderManager:registerResource("SoftShadowMapping","VertexFragment","Data/Shader/softShadowMapping.vert","Data/Shader/softShadowMapping.frag")

ShaderManager:registerResource("SmokeParticles","VertexGeometryFragment","Data/Shader/smokeParticles.vert","Data/Shader/smokeParticles.frag","Data/Shader/smokeParticles.geom")


ShaderManager:registerResource("ONeil","VertexFragment","Data/Shader/oneil.vert","Data/Shader/oneil.frag")

