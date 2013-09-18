#version 330

uniform samplerRect FrameBuffer;
in vec2 TexCoord;
out vec4 fragColor;

void main()
{
    vec4 sum = vec4(0);
    int j;
    int i;

    for( i= -4 ;i < 4; i++)
    {
	    for (j = -3; j < 3; j++)
        {
			//0.25
            sum += texture(FrameBuffer, TexCoord + vec2(j, i)) * 0.25;
        }
    }
    if(texture(FrameBuffer, TexCoord).r < 0.3)
    {
        fragColor = sum*sum*0.012 + texture(FrameBuffer, TexCoord);
    }
    else
    {
        if(texture(FrameBuffer, TexCoord).r < 0.5)
        {
            fragColor = sum*sum*0.009 + texture(FrameBuffer, TexCoord);
        }
        else
        {
            fragColor = sum*sum*0.0075 + texture(FrameBuffer, TexCoord);
        }
    }
}
