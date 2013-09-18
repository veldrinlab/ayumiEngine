#version 330

#define MAX_LIGHTS_NUM 8
#define DIR_NUM 1
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

uniform struct SpotLight
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

in vec4 vertex;
in vec3 normal;
in vec2 texCoord;
in vec4 tangent;

out vec3 ViewDir;
out vec2 TexCoord;

out vec3 dirLightDir[MAX_LIGHTS_NUM];
out vec3 pointLightDir[MAX_LIGHTS_NUM];
out vec3 spotLightDir[MAX_LIGHTS_NUM];
out vec3 spotDir[MAX_LIGHTS_NUM];


void main()
{
	// Create a matrix to transform vectors from eye space to tangent space.

	vec3 n = normalize(normalMatrix * normal);
    vec3 t = normalize(normalMatrix * tangent.xyz);
    vec3 b = cross(n, t) * tangent.w;
    
    mat3 tbnMatrix = mat3(t.x, b.x, n.x,
                          t.y, b.y, n.y,
                          t.z, b.z, n.z);

	// All vertex shaders should write the transformed homogeneous clip space
	// vertex position into the gl_Position variables.

	mat4 modelViewMatrix = viewMatrix * modelMatrix;
    vec4 pos = vertex;
    
    gl_Position = projectionMatrix*modelViewMatrix*pos;
    
    pos = modelViewMatrix * pos;
	ViewDir = -(pos.xyz / pos.w);
	ViewDir = tbnMatrix * ViewDir;

	// Directional Lights
	for(int i = 0; i < DIR_NUM; i++)
	{
		dirLightDir[i] = vec3(viewMatrix * vec4(-directionalLight[i].direction, 0.0f));
		dirLightDir[i] = tbnMatrix * dirLightDir[i];
	}
	    
    TexCoord = texCoord;
}
