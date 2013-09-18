// SkyDome shader
// Author: Szymon "Veldrin" Jab³oñski"
// Date: 11.11.2011

#version 330

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

in vec4 vertex;
in vec2 texCoord;
out vec2 TexCoord;

void main()
{						  
	gl_Position = projectionMatrix*modelViewMatrix*vertex;
    TexCoord = texCoord;
}
