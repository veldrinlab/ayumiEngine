// CellShading / Toon Shading fragment shader
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

uniform sampler1D ToonMap;

in vec3 eyeNormal;
out vec4 fragColor;

void main()
{
	vec4 color;
	vec3 n = normalize(eyeNormal);
	float textureCoordinate = max(0.0, dot(pointLight[0].position,n));
	color = texture(ToonMap, textureCoordinate);
	fragColor = color;
}