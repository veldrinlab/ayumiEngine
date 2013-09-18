-- Material script

-- bazowe dane materialu
Name = "ONeil"
ShaderName = "ONeil"
updateFunctor = "oneil"
depthTest = "false"
backFaceCull = "false"
Ambient = {1.0, 1.0, 1.0, 1.0}
Diffuse = {1.0, 1.0, 1.0, 1.0}
Specular = {1.0, 1.0, 1.0, 1.0}
Shininess = 60

-- dane opcjonalne
lightDirection = {0.0, 1.0, 0.0}
waveLength = {5.60205,9.47328,19.6438}
sunBrightness = 20.0
rayleighConstant = 0.0025
mieConstant = 0.0015
skyRadius = 10.0
scatteringSymmetry = -0.991
samples = 2

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
Material:loadEffectVectorUniform("waveLength",waveLength)
Material:loadMaterialFloatParameter("rayleighConstantSun",rayleighConstant*sunBrightness)
Material:loadMaterialFloatParameter("mieConstantSun",mieConstant*sunBrightness)
Material:loadMaterialFloatParameter("rayleighConstant",rayleighConstant*4*3.14)
Material:loadMaterialFloatParameter("mieConstant",mieConstant*4*3.14)
Material:loadMaterialFloatParameter("skyRadius",skyRadius)
Material:loadMaterialFloatParameter("scatteringSymmetry",scatteringSymmetry)
Material:loadMaterialFloatParameter("scatteringSymmetry2",scatteringSymmetry*scatteringSymmetry)
Material:loadMaterialIntegerParameter("samples",samples)
