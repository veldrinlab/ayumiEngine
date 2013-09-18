-- Shader resource load script
-- Szymon "Veldrin" Jab³oñski
-- 23.04.2011

-- shader data

-- communication with Engine

ShaderManager:registerResource("Skybox","VertexFragment","Data/Shader/skybox.vert","Data/Shader/skybox.frag")

ShaderManager:registerResource("TextureMapping","VertexFragment","Data/Shader/textureMapping.vert","Data/Shader/textureMapping.frag")

ShaderManager:registerResource("ShadowMapping","VertexFragment","Data/Shader/shadowMapping.vert","Data/Shader/shadowMapping.frag")
ShaderManager:registerResource("SoftShadowMapping","VertexFragment","Data/Shader/softShadowMapping.vert","Data/Shader/softShadowMapping.frag")

