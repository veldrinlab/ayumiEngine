#version 330

uniform samplerCube cubemap;
in vec3 cubeMapVector;

out vec4 fragColor;
void main()
{
	vec4 environmentColor;
	environmentColor = texture(cubemap, cubeMapVector);
	fragColor = environmentColor;
}
