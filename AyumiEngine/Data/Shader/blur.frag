#version 330

uniform samplerRect FrameBuffer;

in vec2 TexCoord;
out vec4 fragColor;

void main()
{
	// Fragment shader for 3*3 Gaussian blur

	const vec2 d1 = vec2(-1.0,-1.0);
	const vec2 d2 = vec2(0.0,        1.0);
	const vec2 d3 = vec2(1.0,  1.0);
	const vec2 d4 = vec2( -1.0,  0.0);
	const vec2 d5 = vec2(0.0,        0.0);
	const vec2 d6 = vec2(1.0,  0.0);
	const vec2 d7 = vec2(-1.0, -1.0);
	const vec2 d8 = vec2(0.0,       -1.0);
	const vec2 d9 = vec2(1.0, -1.0);

	fragColor = 	   0.0625 * texture(FrameBuffer,vec2(TexCoord + d1*4)) + 
                       0.125  * texture(FrameBuffer,vec2(TexCoord + d2*4)) + 
					   0.0625 * texture(FrameBuffer,vec2(TexCoord + d3*4)) + 
                       0.125  * texture(FrameBuffer,vec2(TexCoord + d4*4)) + 
					   0.25   * texture(FrameBuffer,vec2(TexCoord + d5*4)) + 
                       0.125  * texture(FrameBuffer,vec2(TexCoord + d6*4)) + 
					   0.0625 * texture(FrameBuffer,vec2(TexCoord + d7*4)) + 
			           0.125  * texture(FrameBuffer,vec2(TexCoord + d8*4)) +
			           0.0625 * texture(FrameBuffer,vec2(TexCoord + d9*4));
					   
	fragColor.a = 1.0f;
}
