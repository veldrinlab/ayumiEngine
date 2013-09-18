//
// Atmospheric scattering fragment shader
// Szymon "Veldrin" Jab�o�ski
// 
// Based on Preetham "A Practical Analytic Model for Daylight" Model
//
//
// Projekt C-Way
// Efekty nieba, chmur i s�o�ca w grze 2D z widokiem z boku
// Szymon Jab�o�ski
// pod kierunkiem Tomasza Martyna
// Instytut Informatyki
// Politechnika Warszawska
//
// version for Ayumi Engine

#version 330

uniform vec3 lightDirection;
uniform vec3 baseColor;
uniform vec3 zenith;
uniform vec3 A;
uniform vec3 B;
uniform vec3 C;
uniform vec3 D;
uniform vec3 E;

in vec2 TexCoord;
in vec3 pos;

out vec4 fragColor;

vec3 xyY_to_XYZ(vec3 src) 
{ 
	float f = (src.z / src.y); 
	return vec3(src.x * f, src.z, (1.0 - src.x - src.y) * f); 
} 
 
vec3 XYZ_to_RGB(vec3 src) 
{ 
	mat3 m = mat3( 
		3.240479, -0.969256, 0.055648, 
		-1.537150, 1.875991, -0.204043, 
		-0.498535, 0.041556, 1.057311); 
	return m * src; 
} 

//gamma - k�t mi�dzy targetem i s�o�cem
//theta - kat mi�dzy tagetem i zenitem

void main()
{
	fragColor = vec4(0.0,0.6,0.0,1.0);
	
	vec3 target = normalize(pos); 			
	float cos_theta = abs(target.y);
	float cos_gamma = dot(lightDirection, target); 
	float gamma = acos(cos_gamma); 
	
	vec3 xyY = (1.0 + A*exp(B/cos_theta)) * (1.0 + C*exp(D*gamma) + E*cos_gamma*cos_gamma);
	vec3 XYZ = xyY_to_XYZ(zenith*xyY);
	
	vec3 RGB = XYZ_to_RGB(XYZ);
		
	fragColor = vec4(RGB, 1.0); 	
}