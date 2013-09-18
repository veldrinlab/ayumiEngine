#version 330

uniform samplerCube cubeMap;

in vec3 fragmentNormal;
in vec3 fragmentReflection;

out vec4 fragColor;

void main(void)
{
	float intensity;
	vec4 environmentColor = texture(cubeMap, fragmentReflection);
	intensity = max(dot(fragmentNormal, vec3(0.0, 0.0, 1.0)), 0.0);
	fragColor = environmentColor * intensity;
}
