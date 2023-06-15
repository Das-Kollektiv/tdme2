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

{$FUNCTIONS}

// layouts
in vec3 v_Position;
#ifdef HAS_VERTEX_COLOR_VEC3
	in vec3 v_Color;
#endif
#ifdef HAS_VERTEX_COLOR_VEC4
	in vec4 v_Color;
#endif

in vec4 v_EffectColorMul;
in vec4 v_EffectColorAdd;

// uniforms
uniform float u_MetallicFactor;
uniform float u_RoughnessFactor;
uniform vec4 u_BaseColorFactor;
uniform vec3 u_EmissiveFactor;
uniform vec3 u_EmissiveColor;
uniform float u_Exposure;
uniform float u_AlphaCutoff;
uniform int u_AlphaCutoffEnabled;

#ifdef MATERIAL_SPECULARGLOSSINESS
uniform vec3 u_SpecularFactor;
uniform vec4 u_DiffuseFactor;
uniform float u_GlossinessFactor;
#endif

// out
layout (location = 0) out vec3 outPosition;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec4 outMaterialMetallicFactorRoughnessFactorExposureType;
layout (location = 3) out vec4 outMaterialBaseColor;
layout (location = 4) out vec4 outMaterialMetallicRoughness;
layout (location = 5) out vec4 outMaterialEmissiveColor;
layout (location = 6) out vec4 outMaterialEffectColorMul;
layout (location = 7) out vec4 outMaterialEffectColorAdd;


void main(void) {
	// masked transparency
	vec4 baseColor = u_BaseColorSamplerAvailable == 1?getBaseColor():vec4(1.0, 1.0, 1.0, 1.0);
	if (u_AlphaCutoffEnabled == 1) {
		if (baseColor.a < u_AlphaCutoff) discard;
		baseColor.a = 1.0;
	}

	//
	outPosition = v_Position;
	outNormal = getNormal();
	outMaterialMetallicFactorRoughnessFactorExposureType = vec4(u_MetallicFactor, u_RoughnessFactor, u_Exposure, 1.0);
	outMaterialMetallicRoughness = u_MetallicRoughnessSamplerAvailable == 1?getMetallicRoughnessColor():vec4(0.0, 1.0, 1.0, 0.0);
	outMaterialBaseColor = baseColor * vec4(u_BaseColorFactor.rgb, u_BaseColorFactor.a);
	outMaterialEmissiveColor = (u_EmissiveSamplerAvailable == 1?getEmissiveColor():vec4(0.0, 0.0, 0.0, 1.0)) * vec4(u_EmissiveFactor, 1.0);
	outMaterialEffectColorMul = v_EffectColorMul / 5.0;
	outMaterialEffectColorAdd = v_EffectColorAdd;
}
