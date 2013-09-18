-- Forward rendering Lights load script
-- Szymon "Veldrin" Jab³oñski
-- 29.06.2011

-- lights data

-- LIGHT0 - Directional Light
-- LightColor [Ambient, Diffuse, Specular]
 
Name = "LIGHT0"
Type = "Directional"
Ambient = {1.0, 1.0, 1.0, 1.0}
Diffuse = {1.0, 1.0, 1.0, 1.0}
Specular = {1.0, 1.0, 1.0, 1.0}
LightDirection = {0.0, -1.0, 0.0}
LightColor = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 }

-- drugie na zero i fajny motyw
-- LIGHT1 - PointLight

Name2 = "LIGHT1"
Type2 = "Point"
Ambient2 = {1.0, 0.0, 1.0, 1.0}
Diffuse2 = {1.0, 1.0, 1.0, 1.0}
Specular2 = {1.0, 1.0, 1.0, 1.0}
LightPosition = {0.0, 10000.0, 0.0}
Radius = 12500.0

-- communication with Engine

--LightManager:addDirectionalLight("Dir1",LightColor,LightDirection)
LightManager:addPointLight("Point1",LightColor,LightPosition,Radius)