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

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ViewMatrix;


in vec4 vertex;
in vec3 normal;
in vec2 texCoord;

out vec3 VertexPos;
out vec3 LightDir;
out vec3 Normal;
out vec2 TexCoord;

void main()
{						  
    vec4 pos = vertex;   
	gl_Position = modelViewProjectionMatrix * pos;
    
	mat4 modelViewMatrix = ViewMatrix * modelMatrix;
	

    pos = modelViewMatrix * pos;
	VertexPos = pos.xyz / pos.w;
        
	LightDir = vec3(ViewMatrix * vec4(-DirectionalLight1.direction, 0.0f));
    
    Normal = NormalMatrix * normal;
    TexCoord = texCoord;
}
