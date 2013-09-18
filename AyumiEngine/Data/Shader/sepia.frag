#version 330

uniform samplerRect FrameBuffer;

in vec2 TexCoord;
out vec4 fragColor;

void main()
{
	//Sepia matrix
	
	mat4 sepiaMatrix = mat4(0.5, 0.4, 0.2, 0.0,
							0.4, 0.3, 0.2, 0.0,
							0.3, 0.3, 0.2, 0.0,
							0.0, 0.0, 0.0, 1.0);
	
	mat4 colorMatrix = transpose(sepiaMatrix);
	vec4 color = vec4(texture(FrameBuffer,TexCoord).rgb,1.0);
	color = colorMatrix * color;
	fragColor = color / color.a;
}
