#version 330

uniform samplerRect FrameBuffer;
in vec2 TexCoord;
uniform float a;
//uniform float strength;

out vec4 fragColor;

void main()
{
  vec4 suma = vec4(0.0);
  
  int q;
  int w;

  for (q=-3; q<3; q++)
  {
    for (w=-3; w<3; w++)
    {
      suma += texture(FrameBuffer, TexCoord + vec2(w, q) * 0.004);
    }
  }

  suma *= 0.15;
  vec4 te2 = texture(FrameBuffer, TexCoord); 
  fragColor = suma * suma * ((1.0 - te2[0]) * 0.025) + te2;
  fragColor.a = a;
}
