#version 330 core

precision lowp float;

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


	// determine visibility
	vec4 color = vec4(0.0);
	float lookUps = 4;
	vec2 lookUpUV = vec2(u, v);
	for (int y = 0; y < lookUps; y++)
	for (int x = 0; x < lookUps; x++) {
		color+= texture(
			sampler,
			lookUpUV +
				vec2(
					(-lookUps / 2.0 + 0.5 + x) * (1.0f / 2048),
					(-lookUps / 2.0 + 0.5 + y) * (1.0f / 2048)
				)
		);
	}
	color/= (lookUps * lookUps);

	// Sample the spherical panorama texture
	outColor = color * 0.4 + texture(sampler, lookUpUV) * 0.6;
}
