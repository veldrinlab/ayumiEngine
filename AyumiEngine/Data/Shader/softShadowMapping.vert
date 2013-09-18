#version 330

#define MAX_LIGHTS_NUM 8
#define DIR_NUM 0
#define POINT_NUM 1
#define SPOT_NUM 0

uniform struct DirectionalLight
{
	vec3 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
} directionalLight[MAX_LIGHTS_NUM];

uniform struct PointLight
{
	float radius;
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
} pointLight[MAX_LIGHTS_NUM];

uniform struct Spotlight
{
	float range;
	float cosInnerCone;
	float cosOuterCone;
	vec3 position;
	vec3 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
} spotLight[MAX_LIGHTS_NUM];

uniform struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
} material;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;
uniform mat4 shadowMatrix0;

in vec4 vertex;
in vec3 normal;
in vec2 texCoord;

out vec3 VertexPos;
out vec3 Normal;
out vec2 TexCoord;
out vec3 dirLightDir[MAX_LIGHTS_NUM];
out vec3 pointLightDir[MAX_LIGHTS_NUM];
out vec3 spotLightDir[MAX_LIGHTS_NUM];
out vec3 spotDir[MAX_LIGHTS_NUM];
out vec4 projCoord;

void main(void)
{
	vec4 pos = vertex;
	gl_Position = projectionMatrix*modelViewMatrix*pos;
    
	mat4 modelViewMatrix = viewMatrix * modelMatrix;
    pos = modelViewMatrix * pos;
	
	VertexPos = pos.xyz / pos.w;
		
	// dodatek
	dirLightDir[0] = vec3(0.0);
		
	// Directional Lights
	for(int i = 0; i < DIR_NUM; i++)
		dirLightDir[i] = vec3(viewMatrix * vec4(-directionalLight[i].direction, 0.0f));
	
	// Point Lights
    for(int i = 0; i < POINT_NUM; i++)
	{
		pos = viewMatrix * vec4(pointLight[i].position, 1.0);
		vec3 lightPosEye = pos.xyz / pos.w;
		pointLightDir[i] = (lightPosEye - VertexPos) / pointLight[i].radius;
	}
	
	// Spot Lights
	for(int i = 0; i < SPOT_NUM; i++)
	{
		pos = viewMatrix * vec4(spotLight[i].position, 1.0);
		vec3 spotlightPosEye = pos.xyz / pos.w;	
		spotLightDir[i] = (spotlightPosEye - VertexPos) / spotLight[i].range;    
		spotDir[i] = vec3(viewMatrix * vec4(spotLight[i].direction, 0.0));
	}

    Normal = normalMatrix * normal;
    TexCoord = texCoord;
	projCoord = shadowMatrix0*modelViewMatrix*vertex;
}
