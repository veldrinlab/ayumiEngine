-- Material script

Name = "Terrain"
LayerAmount = 2
FirstLayerName = "Grass"
SecondLayerName = "Rock"
ShaderName = "Terrain"

Ambient = {1.0, 1.0, 1.0, 1.0}
Diffuse = {1.0, 1.0, 1.0, 1.0}
Specular = {1.0, 1.0, 1.0, 1.0}
Shininess = 60

Material:loadMaterialName(Name)
Material:loadMaterialLayer(FirstLayerName,0)
Material:loadMaterialLayer(SecondLayerName,1)
Material:loadMaterialShader(ShaderName)
Material:loadMaterialAmbient(Ambient)
Material:loadMaterialDiffuse(Diffuse)
Material:loadMaterialSpecular(Specular)
Material:loadMaterialShininess(Shininess)