#version 330

uniform samplerCube day;
uniform samplerCube night;
uniform float dt; // some mix value from engine timeline
in vec3 cubeMapVector;

out vec4 fragColor;
void main()
{
	vec4 environmentColor;
	environmentColor = mix(texture(day,cubeMapVector),texture(night,cubeMapVector),dt);
	//environmentColor = texture(cube, cubeMapVector);
	fragColor = environmentColor;
}
