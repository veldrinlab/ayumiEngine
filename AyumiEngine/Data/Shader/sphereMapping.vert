#version 330

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 inverseCameraMatrix;

in vec4 vertex;
in vec3 normal;

out vec2 texCoord;

void main(void)
{
	gl_Position = projectionMatrix*modelViewMatrix*vertex;

	vec3 eyeModelView = normalize((modelViewMatrix*vertex).xyz);
	vec3 fragmentNormal = (modelViewMatrix*vec4(normal, 0.0)).xyz; // moze normal matrix

	vec3 r = reflect(eyeModelView,fragmentNormal);
	float m = 2.0 * sqrt( r.x*r.x + r.y*r.y + (r.z+1.0)*(r.z+1.0));
	
	texCoord.x = r.x/m + 0.5;
	texCoord.y = r.y/m + 0.5;
}

