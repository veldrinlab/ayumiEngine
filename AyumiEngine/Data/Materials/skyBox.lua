-- Material script

Name = "Skybox"
LayerAmount = 1
FirstLayerName = "Skybox"
ShaderName = "Skybox"

Ambient = {1.0, 1.0, 1.0, 1.0}
Diffuse = {1.0, 1.0, 1.0, 1.0}
Specular = {1.0, 1.0, 1.0, 1.0}
Shininess = 60

Material:loadMaterialName(Name)
Material:loadMaterialLayer(FirstLayerName,0)
Material:loadMaterialShader(ShaderName)
Material:loadMaterialAmbient(Ambient)
Material:loadMaterialDiffuse(Diffuse)
Material:loadMaterialSpecular(Specular)
Material:loadMaterialShininess(Shininess)