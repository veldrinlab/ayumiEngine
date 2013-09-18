#version 330

uniform samplerRect FrameBuffer;

in vec2 TexCoord;
out vec4 fragColor;

void main()
{
	//Using bilinear interpolation
	
	const vec2	d1 = vec2 (4.0, 4.0);
	const vec2	d2 = vec2 (4.0, -4.0);
	const vec2	d3 = vec2 (-4.0, 4.0);
	const vec2	d4 = vec2 (-4.0, -4.0);

	vec2 p = TexCoord;
	
	fragColor = (texture( FrameBuffer, vec2 ( p + d1 ) ) + 
                       texture ( FrameBuffer, vec2 ( p + d2 ) ) + 
					   texture ( FrameBuffer, vec2 ( p + d3 ) ) + 
			           texture ( FrameBuffer, vec2 ( p + d4 ) ) ) * 0.25;
}





