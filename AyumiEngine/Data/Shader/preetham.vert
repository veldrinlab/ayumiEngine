//
// Atmospheric scattering vertex shader
// Szymon "Veldrin" Jab³oñski
// 
// Based on Preetham "A Practical Analytic Model for Daylight" Model
//
//
// Projekt C-Way
// Efekty nieba, chmur i s³oñca w grze 2D z widokiem z boku
// Szymon Jab³oñski
// pod kierunkiem Tomasza Martyna
// Instytut Informatyki
// Politechnika Warszawska
//
// version for Ayumi Engine

#version 330

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

in vec4 vertex;
in vec2 texCoord;

out vec2 TexCoord;
out vec3 pos;

void main()
{						
	pos = vertex.xyz;
	gl_Position = projectionMatrix*modelViewMatrix*vertex;
    TexCoord = texCoord;
}
