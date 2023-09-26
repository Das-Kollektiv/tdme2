#version 330 core

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

//
uniform sampler2D sampler;
uniform vec3 sideVector;
uniform vec3 upVector;
uniform vec3 forwardVector;

#define PI  3.14159265359f
#define PI2 6.28318530718f

void main(void){
	// Calculate the direction vector based on camera orientation
	vec2 uv = vsFragTextureUV - 0.5;
	vec3 direction = normalize(forwardVector + uv.x * sideVector + uv.y * upVector);

	// Calculate the polar angle (vertical angle)
	float polar = acos(direction.y);

	// Calculate the azimuth angle (horizontal angle)
	float azimuth = atan(direction.z, direction.x);

	// Map the azimuth angle to the [0, 1] range
	float u = (azimuth + PI) / PI2;

	// Map the polar angle to the [0, 1] range
	float v = polar / PI;

	// Sample the spherical panorama texture
	outColor = texture(sampler, vec2(u, v));
}
