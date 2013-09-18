#version 330

uniform mat4 modelViewProjectionMatrix;

in vec4 vertex;

out vec3 cubeMapVector;

void main()
{
	cubeMapVector = normalize(vertex.xyz);
    gl_Position = modelViewProjectionMatrix * vertex;
}