-- Texture resource load script
-- Szymon "Veldrin" Jab³oñski
-- 22.04.2011

-- texture data

-- communication with Engine

-- ogolne
TextureManager:registerResource("Font","Data/Texture/font.png","TEXTURE_RECT")
TextureManager:registerResource("AyumiLogo","Data/Texture/ayumiLogo.png","TEXTURE_RECT")

-- do terrain demo
TextureManager:registerResource("Grass","Data/Texture/grass.png","TEXTURE2D")
TextureManager:registerResource("Rock","Data/Texture/rock.png","TEXTURE2D")
TextureManager:registerResource("F16","Data/Texture/f16.png","TEXTURE2D")
TextureManager:registerResource("Missile","Data/Texture/missile.png","TEXTURE2D")
TextureManager:registerResource("SkyDome","Data/Texture/skyDome.png","TEXTURE2D")

-- materials demo

TextureManager:registerResource("Box","Data/Texture/box.jpg","TEXTURE2D")
TextureManager:registerResource("ColorMap","Data/Texture/colorMap.png","TEXTURE2D")
TextureManager:registerResource("GlossMap","Data/Texture/glossMap.png","TEXTURE2D")
TextureManager:registerResource("NormalMap","Data/Texture/normalMap.png","TEXTURE2D")
TextureManager:registerResource("HeightMap","Data/Texture/heightMap.png","TEXTURE2D")
TextureManager:registerResource("ToonMap","Data/Texture/redToon.texture1d","TEXTURE1D")
TextureManager:registerResource("Skybox","Data/Texture/Skybox/left.png","Data/Texture/Skybox/right.png","Data/Texture/Skybox/top.png","Data/Texture/Skybox/bottom.png","Data/Texture/Skybox/back.png","Data/Texture/Skybox/front.png","CUBEMAP")
TextureManager:registerResource("Billboard","Data/Texture/logo.png","TEXTURE2D")

-- fracture demo
TextureManager:registerResource("Metal","Data/Texture/metal.png","TEXTURE2D")
TextureManager:registerResource("Crosshair","Data/Texture/crosshair.png","TEXTURE_RECT")

TextureManager:registerResource("M16","Data/Texture/m16.bmp","TEXTURE2D")
TextureManager:registerResource("Wall","Data/Texture/brick.tga","TEXTURE2D")
TextureManager:registerResource("Particle","Data/Texture/particle.png","TEXTURE2D")

-- csg demo
TextureManager:registerResource("SmoothRock","Data/Texture/smoothRock.png","TEXTURE2D")

-- Animation demo
TextureManager:registerResource("Yoshi","Data/Texture/yoshi.pcx","TEXTURE2D")
