#version 330

layout( points ) in;
layout( triangle_strip, max_vertices = 4 ) out;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform float pointSize;

in vec4 inoutPosition[1];
out vec2 texCoord;

void main()
{
    // rozmiar punktu okreœla rozmiar prostok¹ta
    float pointHalfSize = 0.0075 * pointSize;

    // pierwszy wierzcho³ek
    gl_Position = projectionMatrix*modelViewMatrix *
                (inoutPosition[0] + vec4( -pointHalfSize, pointHalfSize, 0.0, 0.0 ) );
    texCoord = vec2( 0.0, 1.0 );
    EmitVertex();

    // drugi wierzcho³ek
    gl_Position = projectionMatrix*modelViewMatrix *
                (inoutPosition[0] + vec4( -pointHalfSize, -pointHalfSize, 0.0, 0.0 ) );
    texCoord = vec2( 0.0, 0.0 );
    EmitVertex();

    // trzeci wierzcho³ek
    gl_Position = projectionMatrix*modelViewMatrix *
                (inoutPosition[0] + vec4( pointHalfSize, pointHalfSize, 0.0, 0.0 ) );
    texCoord = vec2( 1.0, 1.0 );
    EmitVertex();

    // czwarty wierzcho³ek
    gl_Position = projectionMatrix*modelViewMatrix *
                (inoutPosition[0] + vec4( pointHalfSize, -pointHalfSize, 0.0, 0.0 ) );
    texCoord = vec2( 1.0, 0.0 );
    EmitVertex();

    // koniec prymitywu
    EndPrimitive();
}
