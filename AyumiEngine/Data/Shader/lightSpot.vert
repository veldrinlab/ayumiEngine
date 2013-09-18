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

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ViewMatrix;

in vec4 vertex;
in vec3 normal;
in vec2 texCoord;


out vec3 VertexPos;
out vec3 LightDir;
out vec3 SpotlightDir;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    vec4 pos = vertex;   
	gl_Position = modelViewProjectionMatrix * pos;
    
	mat4 modelViewMatrix = ViewMatrix * modelMatrix;
	
    pos = modelViewMatrix * pos;
	VertexPos = pos.xyz / pos.w;

	// Transform the spotlight position into eye space.
	// Spotlights are specified in world space.
	
	pos = ViewMatrix * vec4(Spotlight1.position, 1.0);
	
	vec3 spotlightPosEye = pos.xyz / pos.w;
        
    // Calculate the light direction. This is the direction from the vertex
    // position to the spotlight position. The division by the spotlight range
    // is used for the attenuation calculation in the fragment shader.
	
	LightDir = (spotlightPosEye - VertexPos) / Spotlight1.range;
    
    // Transform the spotlight direction into eye space.
    // This is the direction that the spotlight is pointing.
    
    SpotlightDir = vec3(ViewMatrix * vec4(Spotlight1.direction, 0.0));
    Normal = NormalMatrix * normal;
    TexCoord = texCoord;
}
