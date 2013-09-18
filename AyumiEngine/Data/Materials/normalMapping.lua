-- Material script

Name = "NormalMapping"
LayerAmount = 3
FirstLayerName = "ColorMap"
SecondLayerName = "GlossMap"
ThirdLayerName = "NormalMap"
ShaderName = "NormalMapping"

Ambient = {0.3, 0.3, 0.3, 1.0}
Diffuse = {0.7, 0.7, 0.7, 1.0}
Specular = {0.5, 0.5, 0.5, 1.0}
Shininess = 60

Material:loadMaterialName(Name)
Material:loadMaterialLayer(FirstLayerName,0)
Material:loadMaterialLayer(SecondLayerName,1)
Material:loadMaterialLayer(ThirdLayerName,2)
Material:loadMaterialShader(ShaderName)
Material:loadMaterialAmbient(Ambient)
Material:loadMaterialDiffuse(Diffuse)
Material:loadMaterialSpecular(Specular)
Material:loadMaterialShininess(Shininess)