-- Material script

Name = "Skybox"
LayerAmount = 2
FirstLayerName = "Day"
SecondLayerName = "Night"
ShaderName = "DayAndNight"

Ambient = {1.0, 1.0, 1.0, 1.0}
Diffuse = {1.0, 1.0, 1.0, 1.0}
Specular = {1.0, 1.0, 1.0, 1.0}
Shininess = 60

Material:loadMaterialName(Name)
Material:loadLayerAmount(LayerAmount)
Material:loadMaterialLayer(FirstLayerName)
Material:loadMaterialLayer(SecondLayerName)
Material:loadMaterialShader(ShaderName)
Material:loadMaterialAmbient(Ambient)
Material:loadMaterialDiffuse(Diffuse)
Material:loadMaterialSpecular(Specular)
Material:loadMaterialShininess(Shininess)
Material:loadLayerName("Day")
Material:loadLayerName("Night")