#version 330 core

// TODO: maybe move me into definitions
#ifndef HAVE_PBRLIGHT_STRUCT
#define HAVE_PBRLIGHT_STRUCT
struct PBRLight {
    int enabled;

    vec3 direction;
    float range;

    vec3 color;
    float intensity;

    vec3 position;
    float innerConeCos;

    float outerConeCos;
    int type;
};
#endif

{$DEFINITIONS}

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
	vec4 fragmentParameters = texture(geometryBufferTextureId3, vsFragTextureUV);
	int type = int(fragmentParameters[3]);
	#if defined(HAVE_DEPTH_FOG)
		float fragDepth = fragmentParameters[2];
		float fogStrength = 0.0;
		if (fragDepth > FOG_DISTANCE_NEAR) {
			fogStrength = (clamp(fragDepth, FOG_DISTANCE_NEAR, FOG_DISTANCE_MAX) - FOG_DISTANCE_NEAR) * 1.0 / (FOG_DISTANCE_MAX - FOG_DISTANCE_NEAR);
		}
	#endif
	if (type == 0) {
		// specular
		#if defined(HAVE_DEPTH_FOG)
			if (fogStrength < 1.0) {
		#endif
		SpecularMaterial specularMaterial;
		specularMaterial.diffuse = texture(colorBufferTextureUnit2, vsFragTextureUV);
		if (specularMaterial.diffuse.a < 0.001) discard;
		specularMaterial.ambient = texture(colorBufferTextureUnit1, vsFragTextureUV);
		specularMaterial.specular = texture(colorBufferTextureUnit3, vsFragTextureUV);
		specularMaterial.emission = texture(colorBufferTextureUnit4, vsFragTextureUV);
		specularMaterial.shininess = fragmentParameters[0];
		specularMaterial.reflection = fragmentParameters[1];
		vec3 position = texture(geometryBufferTextureId1, vsFragTextureUV).xyz;
		vec3 normal = texture(geometryBufferTextureId2, vsFragTextureUV).xyz;
		vec4 diffuse = texture(colorBufferTextureUnit5, vsFragTextureUV);
		vec4 fragColor = specularMaterial.emission + computeSpecularLighting(normal, position, normalize(vec3(cameraMatrix * -vec4(position, 0.0))), specularMaterial);
		outColor = clamp(fragColor * diffuse, 0.0, 1.0);
		outColor.a = specularMaterial.diffuse.a;
		#if defined(HAVE_DEPTH_FOG)
			}
		#endif
	} else
	if (type == 1) {
		fogStrength = 0.00001; // TODO: fog
		// pbr
		PBRMaterial pbrMaterial;
		pbrMaterial.metallicFactor = fragmentParameters[0];
		pbrMaterial.roughnessFactor = fragmentParameters[1];
		pbrMaterial.baseColorFactor = texture(colorBufferTextureUnit3, vsFragTextureUV);
		pbrMaterial.exposure = fragmentParameters[2];
		pbrMaterial.alphaCutoff = -1;
		pbrMaterial.alphaCutoffEnabled = -1;
		#ifdef MATERIAL_SPECULARGLOSSINESS
			pbrMaterial.specularFactor = ...
			pbrMaterial.diffuseFactor = ...
			pbrMaterial.glossinessFactor = ...
		#endif
		pbrMaterial.normalSamplerAvailable = -1;
		pbrMaterial.baseColorSamplerAvailable = -1;
		pbrMaterial.metallicRoughnessSamplerAvailable = -1;
		pbrMaterial.normal = texture(geometryBufferTextureId2, vsFragTextureUV).xyz;
		#ifdef MATERIAL_SPECULARGLOSSINESS
			pbrMaterial.specularGlossinessColor = ...
		#endif
		#ifdef HAS_DIFFUSE_MAP
			pbrMaterial.diffuseColor = ...
		#endif
		pbrMaterial.vertexColor = vec4(1.0, 1.0, 1.0, 1.0);
		pbrMaterial.metallicRoughnessColor = texture(colorBufferTextureUnit2, vsFragTextureUV);
		pbrMaterial.baseColor = texture(colorBufferTextureUnit1, vsFragTextureUV);
		#ifdef DEBUG_NORMAL
			pbrMaterial.normalColor = ...
		#endif

		//
		vec3 position = texture(geometryBufferTextureId1, vsFragTextureUV).xyz;
		outColor = computePBRLighting(position, pbrMaterial);
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
