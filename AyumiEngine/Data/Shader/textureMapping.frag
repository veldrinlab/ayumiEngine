// Texture Mapping with Forward Rendering.
// Author: Szymon "Veldrin" Jab³oñski"
// Date: 30.06.2011

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

uniform sampler2D ColorMap;

in vec3 VertexPos;
in vec3 Normal;
in vec2 TexCoord;
in vec3 dirLightDir[MAX_LIGHTS_NUM];
in vec3 pointLightDir[MAX_LIGHTS_NUM];
in vec3 spotLightDir[MAX_LIGHTS_NUM];
in vec3 spotDir[MAX_LIGHTS_NUM];

out vec4 fragColor;

void main()
{
	vec4 texel = texture(ColorMap, TexCoord);
	vec3 N = normalize(Normal);
	vec3 V = normalize(-VertexPos);
	
	// Directional Lights
	for(int i = 0; i < DIR_NUM; i++)
	{
		vec3 L = normalize(dirLightDir[i]);
		vec3 R = normalize(-reflect(L, N));

		float nDotL = max(0.0, dot(N, L));
		float rDotV = max(0.0, dot(R, V));
	
		vec4 ambient = directionalLight[i].ambient * material.ambient;
		vec4 diffuse = directionalLight[i].diffuse * material.diffuse * nDotL;
		vec4 specular = directionalLight[i].specular * material.specular * pow(rDotV, material.shininess);

		fragColor += (ambient + diffuse + specular) * texel;
	}
	
	// Point Lights
	for(int i = 0; i < POINT_NUM; i++)
	{			
		float atten = max(0.0, 1.0 - dot(pointLightDir[i], pointLightDir[i]));

		vec3 L = normalize(pointLightDir[i]);
		vec3 R = normalize(-reflect(L, N));

		float nDotL = max(0.0, dot(N, L));
		float rDotV = max(0.0, dot(R, V));
	
		vec4 ambient = pointLight[i].ambient * material.ambient * atten;
		vec4 diffuse = pointLight[i].diffuse * material.diffuse * nDotL * atten;
		vec4 specular = pointLight[i].specular * material.specular * pow(rDotV, material.shininess) * atten;
		
		fragColor += (ambient + diffuse + specular) * texel;
	}
	
	// Spot Lights
	for(int i = 0; i < SPOT_NUM; i++)
	{
		float atten = max(0.0, 1.0 - dot(spotLightDir[i], spotLightDir[i]));

		vec3 L = normalize(spotLightDir[i]);
		vec3 SL = normalize(spotDir[i]);
		vec3 R = normalize(-reflect(L, N));

		float spotDot = dot(-L, SL);
		float spotEffect = smoothstep(spotLight[i].cosOuterCone, spotLight[i].cosInnerCone, spotDot);
	
		atten *= spotEffect;
	
		float nDotL = max(0.0, dot(N, L));
		float rDotV = max(0.0, dot(R, V));
	
		vec4 ambient = spotLight[i].ambient * material.ambient * atten;
		vec4 diffuse = spotLight[i].diffuse * material.diffuse * nDotL * atten;
		vec4 specular = spotLight[i].specular * material.specular * pow(rDotV, material.shininess) * atten;
	
		fragColor += (ambient + diffuse + specular) * texel;	
	}
}