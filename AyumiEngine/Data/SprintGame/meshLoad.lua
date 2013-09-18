-- Mesh resource load script
-- Szymon "Veldrin" Jab³oñski
-- 23.04.2011

-- mesh data
-- communication with Engine

-- Drag Race game
MeshManager:registerResource("Vehicle","MESH_VEL","Data/Mesh/vehicle.vel")
MeshManager:registerResource("Course1","MESH_VEL","Data/Mesh/course1.vel")
MeshManager:registerResource("Course2","MESH_VEL","Data/Mesh/course2.vel")

MeshManager:setRawParameters(256,50.0,50.0,950.0,1.0)
MeshManager:registerResource("Terrain","RAW","Data/Mesh/terrainDemo.raw")
MeshManager:registerResource("SkyDome","MESH_VEL","Data/Mesh/skyDome.vel")
MeshManager:registerResource("Box","MESH_VEL","Data/Mesh/cube.vel")

--
MeshManager:registerResource("Sphere","MESH_VEL","Data/Mesh/sphere.vel")


