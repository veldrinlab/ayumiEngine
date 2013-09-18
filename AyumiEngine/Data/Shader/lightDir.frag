#version 150

uniform struct DirectionalLight
{
	vec3 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
} DirectionalLight1;

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
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	vec3 L = normalize(LightDir);
	vec3 N = normalize(Normal);
	vec3 V = normalize(-VertexPos);
	vec3 R = normalize(-reflect(L, N));

	float nDotL = max(0.0, dot(N, L));
	float rDotV = max(0.0, dot(R, V));
	
	vec4 ambient = DirectionalLight1.ambient * Material1.ambient;
	vec4 diffuse = DirectionalLight1.diffuse * Material1.diffuse * nDotL;
	vec4 specular = vec4(1.0,1.0,1.0,1.0) * Material1.specular * pow(rDotV, Material1.shininess);
	vec4 texel = texture(ColorMapSampler, TexCoord);
	
    FragColor = (ambient + diffuse + specular) * texel;
}