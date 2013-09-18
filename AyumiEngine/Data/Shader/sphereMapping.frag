#version 330

uniform sampler2D sphereMap;

in vec2 texCoord;
out vec4 fragColor;

void main(void)
{
	vec4 environmentColor = texture(sphereMap, texCoord);
	fragColor = environmentColor;
}