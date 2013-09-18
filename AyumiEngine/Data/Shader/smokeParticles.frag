#version 330
uniform sampler2D particleMap;
uniform vec4 color;

in vec2 texCoord;
out vec4 outColor;

void main()
{
    vec4 sample = texture(particleMap, texCoord );

    if( sample.r + sample.g + sample.b < 0.2 )
        discard;
    else
        outColor = sample;
	

	
	//outColor -= color;
}
