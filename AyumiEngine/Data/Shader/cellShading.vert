// CellShading / Toon Shading vertex shader
// Author: Szymon "Veldrin" Jab³oñski"
// Date: 30.07.2011

#version 330

#define MAX_LIGHTS_NUM 8
#define POINT_NUM 1

uniform struct PointLight
{
	float radius;
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
} pointLight[MAX_LIGHTS_NUM];

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;

in vec4 vertex;
in vec3 normal;
in vec2 texCoord;
	
out vec3 eyeNormal;

void main()
{		
	eyeNormal = normalMatrix * normal;
	gl_Position = projectionMatrix*modelViewMatrix*vertex;
}