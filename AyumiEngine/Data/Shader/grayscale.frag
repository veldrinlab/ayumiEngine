#version 330

uniform samplerRect FrameBuffer;

in vec2 TexCoord;
out vec4 fragColor;

void main()
{
	//Grayscale matrix
	
	mat4 grayscaleMatrix = mat4(0.3, 0.6, 0.1, 0.0,
								0.3, 0.6, 0.1, 0.0,
								0.3, 0.6, 0.1, 0.0,
								0.0, 0.0, 0.0, 1.0);
	
	mat4 colorMatrix = transpose(grayscaleMatrix);
	vec4 color = vec4(texture(FrameBuffer,TexCoord).rgb,1.0);
	color = colorMatrix * color;
	fragColor = color / color.a;
}
