#version 330 core

{$DEFINITIONS}

// TODO: maybe move me into definitions
struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
	float reflection;
};

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

{$FUNCTIONS}

#if defined(HAVE_DEPTH_FOG)
	#define FOG_DISTANCE_NEAR			100.0
	#define FOG_DISTANCE_MAX				250.0
	#define FOG_RED						(255.0 / 255.0)
	#define FOG_GREEN					(255.0 / 255.0)
	#define FOG_BLUE						(255.0 / 255.0)
#endif

// main
void main(void) {
	outColor = vec4(1.0, 0.0, 0.0, 1.0);
	vec4 shininessReflectionFragDepthType = texture(geometryBufferTextureId3, vsFragTextureUV).xyzw;
	int type = int(shininessReflectionFragDepthType.w);
	#if defined(HAVE_DEPTH_FOG)
		float fragDepth = shininessReflectionFragDepthType.z;
		float fogStrength = 0.0;
		if (fragDepth > FOG_DISTANCE_NEAR) {
			fogStrength = (clamp(fragDepth, FOG_DISTANCE_NEAR, FOG_DISTANCE_MAX) - FOG_DISTANCE_NEAR) * 1.0 / (FOG_DISTANCE_MAX - FOG_DISTANCE_NEAR);
		}
	#endif
	if (type == 0) {
		#if defined(HAVE_DEPTH_FOG)
			if (fogStrength < 1.0) {
		#endif
		Material material;
		material.diffuse = texture(colorBufferTextureUnit2, vsFragTextureUV).rgba;
		if (material.diffuse.a < 0.001) discard;
		float fragDepth = shininessReflectionFragDepthType.z;
		material.ambient = texture(colorBufferTextureUnit1, vsFragTextureUV).rgba;
		material.specular = texture(colorBufferTextureUnit3, vsFragTextureUV).rgba;
		material.emission = texture(colorBufferTextureUnit4, vsFragTextureUV).rgba;
		material.shininess = shininessReflectionFragDepthType.x;
		material.reflection = shininessReflectionFragDepthType.y;
		vec3 position = texture(geometryBufferTextureId1, vsFragTextureUV).xyz;
		vec3 normal = texture(geometryBufferTextureId2, vsFragTextureUV).xyz;
		vec4 diffuse = texture(colorBufferTextureUnit5, vsFragTextureUV).rgba;
		vec4 fragColor = material.emission + computeSpecularLighting(normal, position, normalize(vec3(cameraMatrix * -vec4(position, 0.0))), material);
		outColor = clamp(fragColor * diffuse, 0.0, 1.0);
		outColor.a = material.diffuse.a;
		#if defined(HAVE_DEPTH_FOG)
			}
		#endif
	} else
	if (type == 1) {
		// pbr
	}
	gl_FragDepth = texture(depthBufferTextureUnit, vsFragTextureUV).r;
	#if defined(HAVE_DEPTH_FOG)
		if (fogStrength > 0.0) {
			outColor = vec4(
				(outColor.rgb * (1.0 - fogStrength)) +
				vec3(FOG_RED, FOG_GREEN, FOG_BLUE) * fogStrength,
				1.0
			);
		}
	#endif
}
