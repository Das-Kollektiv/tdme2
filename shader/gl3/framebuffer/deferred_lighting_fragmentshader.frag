#version 330 core

#define FALSE		0
#define MAX_LIGHTS	8

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
	float reflection;
};

struct Light {
	int enabled;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
	vec3 spotDirection;
	float spotExponent;
	float spotCosCutoff;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

uniform Light lights[MAX_LIGHTS];

// uniforms
uniform mat4 cameraMatrix;
uniform sampler2D geometryBufferTextureId1;
uniform sampler2D geometryBufferTextureId2;
uniform sampler2D geometryBufferTextureId3;
uniform sampler2D colorBufferTextureUnit1;
uniform sampler2D colorBufferTextureUnit2;
uniform sampler2D colorBufferTextureUnit3;
uniform sampler2D colorBufferTextureUnit4;
uniform sampler2D colorBufferTextureUnit5;
uniform sampler2D depthBufferTextureUnit;

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

//
vec4 computeLight(in int i, in vec3 normal, in vec3 position, in Material material) {
	vec3 vsEyeDirection = normalize(vec3(cameraMatrix * -vec4(position, 0.0)));
	vec3 lightDirection = lights[i].position.xyz - position.xyz;
	float lightDistance = length(lightDirection);
	lightDirection = normalize(lightDirection);
	vec3 reflectionDirection = normalize(reflect(-lightDirection, normal));

	// compute attenuation
	float lightAttenuation =
		1.0 /
		(
			lights[i].constantAttenuation +
			lights[i].linearAttenuation * lightDistance +
			lights[i].quadraticAttenuation * lightDistance * lightDistance
		);

	// see if point on surface is inside cone of illumination
	float lightSpotDot = dot(-lightDirection, normalize(lights[i].spotDirection));
	float lightSpotAttenuation = 0.0;
	if (lightSpotDot >= lights[i].spotCosCutoff) {
		lightSpotAttenuation = pow(lightSpotDot, lights[i].spotExponent);
	}

	// Combine the spotlight and distance attenuation.
	lightAttenuation *= lightSpotAttenuation;

	// add color components to fragment color
	return
		clamp(lights[i].ambient * material.ambient, 0.0, 1.0) +
		clamp(lights[i].diffuse * material.diffuse * max(dot(normal, lightDirection), 0.0) * lightAttenuation, 0.0, 1.0) +
		clamp(lights[i].specular * material.specular * pow(max(dot(reflectionDirection, vsEyeDirection), 0.0), 0.3 * material.shininess) * lightAttenuation, 0.0, 1.0);
}

//
vec4 computeLights(in vec3 normal, in vec3 position, in Material material) {
	vec4 fragColor = vec4(0.0, 0.0, 0.0, 0.0);
	// process each light
	for (int i = 0; i < MAX_LIGHTS; i++) {
		// skip on disabled lights
		if (lights[i].enabled == FALSE) continue;

		// compute light
		fragColor+= computeLight(i, normal, position, material);
	}
	//
	return fragColor;
}

// main
void main(void) {
	Material material;
	material.diffuse = texture(colorBufferTextureUnit2, vsFragTextureUV).rgba;
	if (material.diffuse.a < 0.001) discard;
	vec2 shininessReflection = texture(geometryBufferTextureId3, vsFragTextureUV).xy;
	material.ambient = texture(colorBufferTextureUnit1, vsFragTextureUV).rgba;
	material.specular = texture(colorBufferTextureUnit3, vsFragTextureUV).rgba;
	material.emission = texture(colorBufferTextureUnit4, vsFragTextureUV).rgba;
	material.shininess = shininessReflection.x;
	material.reflection = shininessReflection.y;
	vec3 position = texture(geometryBufferTextureId1, vsFragTextureUV).xyz;
	vec3 normal = texture(geometryBufferTextureId2, vsFragTextureUV).xyz;
	vec4 diffuse = texture(colorBufferTextureUnit5, vsFragTextureUV).rgba;
	vec4 fragColor = material.emission + computeLights(normal, position, material);
	outColor = clamp(fragColor * diffuse, 0.0, 1.0);
	outColor.a = material.diffuse.a;
	gl_FragDepth = texture(depthBufferTextureUnit, vsFragTextureUV).r;
}
