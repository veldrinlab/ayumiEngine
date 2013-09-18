#version 330

uniform samplerRect FrameBuffer;
uniform float exposure; 
uniform float decay;
uniform float density;
uniform float weight;
uniform float lightPositionOnScreenX;
uniform float lightPositionOnScreenY;

in vec2 TexCoord;
out vec4 fragColor;

const int NUM_SAMPLES = 100;

void main()
{
	vec2 lightPos = vec2(lightPositionOnScreenX,lightPositionOnScreenY);
	
	vec2 deltaTextCoord = vec2(TexCoord - lightPos.xy);	
	vec2 textCoo = TexCoord;
	deltaTextCoord *= 1.0 /  float(NUM_SAMPLES) * density;
	float illuminationDecay = 1.0;
	
	for(int i=0; i < NUM_SAMPLES ; i++)
	{
		textCoo -= deltaTextCoord;
		vec4 sample = texture(FrameBuffer, textCoo);
		sample *= illuminationDecay * weight;	
		fragColor += sample;
		illuminationDecay *= decay;
	}	
	fragColor *= exposure;
	fragColor += texture(FrameBuffer, TexCoord);
}