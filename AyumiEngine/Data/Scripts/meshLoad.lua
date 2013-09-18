-- Mesh resource load script
-- Szymon "Veldrin" Jab³oñski
-- 23.04.2011

-- mesh data

-- communication with Engine

-- terrain demo
MeshManager:setRawParameters(256,50.0,50.0,1500.0,1.0)
MeshManager:registerResource("Terrain","RAW","Data/Mesh/terrainDemo.raw")
MeshManager:registerResource("SkyDome","MESH_VEL","Data/Mesh/skyDome.vel")
--MeshManager:registerResource("F16","MESH_VEL","Data/Mesh/f16.vel")
--MeshManager:registerResource("Missile","MESH_VEL","Data/Mesh/missile.vel")

-- materials demo
MeshManager:registerResource("Sphere","MESH_VEL","Data/Mesh/sphere.vel")
--MeshManager:registerResource("Torus","MESH_VEL","Data/Mesh/torus.vel")
MeshManager:registerResource("Box","MESH_VEL","Data/Mesh/cube.vel")

-- fracture demo
--MeshManager:registerResource("Ground","MESH_VEL","Data/Mesh/ground.vel")
--MeshManager:registerResource("M16","MESH_OBJ","Data/Mesh/m16.obj")
--MeshManager:registerResource("Fracture","MESH_VEL","Data/Mesh/fracture.vel")
--MeshManager:registerResource("Fracture1","MESH_VEL","Data/Mesh/fracture1.vel")
--MeshManager:registerResource("Fracture2","MESH_VEL","Data/Mesh/fracture2.vel")
--MeshManager:registerResource("Fracture3","MESH_VEL","Data/Mesh/fracture3.vel")
--MeshManager:registerResource("Fracture4","MESH_VEL","Data/Mesh/fracture4.vel")

-- animation demo
--MeshManager:registerResource("Yoshi","MESH_MD2","Data/Mesh/yoshi.md2")

-- csg demo
--MeshManager:registerResource("Box2","MESH_VEL","Data/Mesh/cube2.vel")

