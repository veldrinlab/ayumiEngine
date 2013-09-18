-- Texture resource load script
-- Szymon "Veldrin" Jab³oñski
-- 22.04.2011

-- texture data

-- communication with Engine

-- ogolne
TextureManager:registerResource("Font","Data/Texture/font.png","TEXTURE_RECT")
TextureManager:registerResource("AyumiLogo","Data/Texture/ayumiLogo.png","TEXTURE_RECT")

TextureManager:registerResource("Skybox","Data/Texture/Skybox/left.png","Data/Texture/Skybox/right.png","Data/Texture/Skybox/top.png","Data/Texture/Skybox/bottom.png","Data/Texture/Skybox/back.png","Data/Texture/Skybox/front.png","CUBEMAP")

TextureManager:registerResource("Crosshair","Data/Texture/crosshair.png","TEXTURE_RECT")
TextureManager:registerResource("M16","Data/Texture/m16.bmp","TEXTURE2D")
TextureManager:registerResource("IntroLogo","Data/Texture/intro.png","TEXTURE_RECT")
TextureManager:registerResource("Metal","Data/Texture/metal.png","TEXTURE2D")
TextureManager:registerResource("Target","Data/Texture/target.png","TEXTURE2D")
