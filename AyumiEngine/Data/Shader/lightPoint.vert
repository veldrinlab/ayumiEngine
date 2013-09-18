#version 150

uniform struct PointLight
{
	vec3 position;
	float radius;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
} PointLight1;

uniform struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
} Material1;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;

in vec4 vertex;
in vec3 normal;
in vec2 texCoord;

out vec3 VertexPos;
out vec3 LightDir;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
	mat4 modelViewMatrix = ViewMatrix * ModelMatrix;
    mat4 mvpMatrix = ProjectionMatrix * modelViewMatrix;
    vec4 pos = vertex;
    
    gl_Position = mvpMatrix * pos;
    
	pos = modelViewMatrix * pos;
	VertexPos = pos.xyz / pos.w;
      
	pos = ViewMatrix * vec4(PointLight1.position, 1.0);
	
	vec3 lightPosEye = pos.xyz / pos.w;
		
	LightDir = (lightPosEye - VertexPos) / PointLight1.radius;
    
    Normal = NormalMatrix * normal;
    TexCoord = texCoord;
}
