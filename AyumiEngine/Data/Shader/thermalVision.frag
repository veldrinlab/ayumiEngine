#version 330

uniform samplerRect FrameBuffer;
uniform float dx;
uniform float dy;

in vec2 TexCoord;
out vec4 fragColor;

void main()
{
	vec4 pixcol = texture(FrameBuffer,TexCoord);
	vec4 colors[3];
	colors[0] = vec4(0.0f,0.0f,1.0f,1.0f);
	colors[1] = vec4(1.0f,1.0f,0.0f,1.0f);
	colors[2] = vec4(1.0f,0.0f,0.0f,1.0f);
	float lum = (pixcol.r+pixcol.g+pixcol.b)/3.0f;
	int ix = (lum < 0.5)? 0:1;
	vec4 thermal = mix(colors[ix],colors[ix+1],(lum-float(ix)*0.5)/0.5);
	fragColor = thermal;
}
