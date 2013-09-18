#version 330

uniform samplerRect FrameBuffer;
uniform float dx;
uniform float dy;

in vec2 TexCoord;
out vec4 fragColor;

void main()
{
	vec2 coord = vec2(dx*floor(TexCoord.x/dx),dy*floor(TexCoord.y/dy));
	fragColor = texture(FrameBuffer, coord);
}
