-- Material script

-- bazowe dane materialu
Name = "Preetham"
ShaderName = "Preetham"
updateFunctor = "preetham"
depthTest = "false"
backFaceCull = "false"
Ambient = {1.0, 1.0, 1.0, 1.0}
Diffuse = {1.0, 1.0, 1.0, 1.0}
Specular = {1.0, 1.0, 1.0, 1.0}
Shininess = 60

-- dane opcjonalne
lightDirection = {-0.987688, -0.156434, 0.0}
baseColor = {1.0, 1.0, 1.0}
zenith = {0.0, 0.0, 0.0}
A = {1.0, 1.0, 1.0}
B = {1.0, 1.0, 1.0}
C = {1.0, 1.0, 1.0}
D = {1.0, 1.0, 1.0}
E = {1.0, 1.0, 1.0}
turbidity = 3.0

-- ladowanie bazowych danych materialu
Material:loadMaterialName(Name)
Material:loadMaterialShader(ShaderName)
Material:loadMaterialUpdateFunctor(updateFunctor)
Material:setDepthTest(depthTest)
Material:setBackFaceCull(backFaceCull)
Material:loadMaterialAmbient(Ambient)
Material:loadMaterialDiffuse(Diffuse)
Material:loadMaterialSpecular(Specular)
Material:loadMaterialShininess(Shininess)

-- ladowanie danych opcjonalny -> modelu efektu nieba
Material:loadEffectVectorUniform("lightDirection",lightDirection)
Material:loadEffectVectorUniform("baseColor",baseColor)
Material:loadEffectVectorUniform("zenith",zenith)
Material:loadEffectVectorUniform("A",A)
Material:loadEffectVectorUniform("B",B)
Material:loadEffectVectorUniform("C",C)
Material:loadEffectVectorUniform("D",D)
Material:loadEffectVectorUniform("E",E)
Material:loadMaterialFloatParameter("turbidity",turbidity)
