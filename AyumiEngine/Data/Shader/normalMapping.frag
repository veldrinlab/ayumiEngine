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

uniform sampler2D ColorMapSampler;
uniform sampler2D GlossMapSampler;
uniform sampler2D NormalMapSampler;


in vec3 ViewDir;
in vec2 TexCoord;
in vec3 dirLightDir[MAX_LIGHTS_NUM];
in vec3 pointLightDir[MAX_LIGHTS_NUM];
in vec3 spotLightDir[MAX_LIGHTS_NUM];
in vec3 spotDir[MAX_LIGHTS_NUM];

out vec4 FragColor;

void main()
{
	// Directional Lights
	for(int i = 0; i < DIR_NUM; i++)
	{
		vec3 L = normalize(dirLightDir[i]);
		vec3 N = normalize(texture(NormalMapSampler, TexCoord.st).xyz * 2.0 - 1.0);
		vec3 V = normalize(ViewDir);
		vec3 R = normalize(-reflect(L, N));

		float nDotL = max(0.0, dot(N, L));
		float rDotV = max(0.0, dot(R, V));
		
		vec4 ambient = directionalLight[i].ambient * material.ambient;
		vec4 diffuse = directionalLight[i].diffuse * material.diffuse * nDotL;
		vec4 specular = directionalLight[i].specular * material.specular * pow(rDotV, material.shininess);
		vec4 texel = texture(ColorMapSampler, TexCoord);
		float gloss = texture(GlossMapSampler, TexCoord).r;
		
		FragColor += (ambient + diffuse + (gloss * specular)) * texel;
	}
}

