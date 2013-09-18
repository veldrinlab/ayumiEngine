#version 330

uniform samplerRect FrameBuffer;

in vec2 TexCoord;
out vec4 fragColor;

void main()
{
	fragColor = texture(FrameBuffer,TexCoord);
}
