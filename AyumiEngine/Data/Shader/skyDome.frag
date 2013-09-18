// SkyDome shader
// Author: Szymon "Veldrin" Jab�o�ski"
// Date: 11.11.2011

#version 330

uniform sampler2D ColorMap;
in vec2 TexCoord;

out vec4 fragColor;

void main()
{
	vec4 texel = texture(ColorMap, TexCoord);
	fragColor = texel;
}