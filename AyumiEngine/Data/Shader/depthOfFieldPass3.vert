#version 330

uniform mat4 modelViewProjectionMatrix;
in vec4 vertex;
in vec2 texCoord;
out vec2 TexCoord;

void main()
{
	gl_Position = modelViewProjectionMatrix * vertex;
	TexCoord = texCoord;
}