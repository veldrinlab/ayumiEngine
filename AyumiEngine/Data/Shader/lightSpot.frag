#version 150

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
} Spotlight1;

uniform struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
} Material1;

uniform sampler2D ColorMapSampler;

in vec3 VertexPos;
in vec3 LightDir;
in vec3 SpotlightDir;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	float atten = max(0.0, 1.0 - dot(LightDir, LightDir));

	vec3 L = normalize(LightDir);
	vec3 SL = normalize(SpotlightDir);
	vec3 N = normalize(Normal);
	vec3 V = normalize(-VertexPos);
	vec3 R = normalize(-reflect(L, N));

	float spotDot = dot(-L, SL);
	float spotEffect = smoothstep(Spotlight1.cosOuterCone, Spotlight1.cosInnerCone, spotDot);
	
	atten *= spotEffect;
	
	float nDotL = max(0.0, dot(N, L));
	float rDotV = max(0.0, dot(R, V));
	
	vec4 ambient = Spotlight1.ambient * Material1.ambient * atten;
	vec4 diffuse = Spotlight1.diffuse * Material1.diffuse * nDotL * atten;
	vec4 specular = Spotlight1.specular * Material1.specular * pow(rDotV, Material1.shininess) * atten;
	vec4 texel = texture(ColorMapSampler, TexCoord);
	
    FragColor = (ambient + diffuse + specular) * texel;
}
