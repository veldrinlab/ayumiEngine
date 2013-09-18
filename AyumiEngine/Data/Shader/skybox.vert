#version 330

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

in vec4 vertex;

out vec3 cubeMapVector;

void main()
{
	cubeMapVector = normalize(vertex.xyz);
    gl_Position = projectionMatrix*modelViewMatrix*vertex;
}