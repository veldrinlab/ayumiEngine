-- Material script

Name = "ShadowFloor"
LayerAmount = 1
FirstLayerName = "Metal"
ShaderName = "SoftShadowMapping"

Ambient = {0.3, 0.3, 0.3, 1.0}
Diffuse = {0.7, 0.7, 0.7, 1.0}
Specular = {0.5, 0.5, 0.5, 1.0}
Shininess = 60

Material:loadMaterialName(Name)
Material:loadMaterialLayer(FirstLayerName,0)
Material:loadMaterialShader(ShaderName)
Material:loadMaterialAmbient(Ambient)
Material:loadMaterialDiffuse(Diffuse)
Material:loadMaterialSpecular(Specular)
Material:loadMaterialShininess(Shininess)