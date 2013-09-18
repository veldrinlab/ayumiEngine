#version 330

uniform samplerRect FrameBuffer;

in vec2 TexCoord;
out vec4 fragColor;

void main()
{
	vec4 color = vec4(texture(FrameBuffer,TexCoord).rgb,1.0);
	fragColor = vec4(1.0-color.x,1.0-color.y,1.0-color.z,1.0);
}
