#version 330 core

#ifdef USE_TEX_LOD
#extension GL_EXT_shader_texture_lod: enable
#endif

#extension GL_OES_standard_derivatives : enable

#ifdef USE_IBL
#extension GL_NV_shadow_samplers_cube : enable
#endif

#ifdef USE_HDR
#extension GL_OES_texture_float : enable
#extension GL_OES_texture_float_linear : enable
#endif

precision highp float;

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

//
uniform float u_MetallicFactor;
uniform float u_RoughnessFactor;
uniform vec4 u_BaseColorFactor;
uniform vec3 u_EmissiveFactor;
uniform float u_Exposure;
uniform float u_AlphaCutoff;
uniform int u_AlphaCutoffEnabled;

#ifdef MATERIAL_SPECULARGLOSSINESS
uniform vec3 u_SpecularFactor;
uniform vec4 u_DiffuseFactor;
uniform float u_GlossinessFactor;
#endif

out vec4 outColor;

void main() {
	PBRMaterial pbrMaterial;
	pbrMaterial.metallicFactor = u_MetallicFactor;
	pbrMaterial.roughnessFactor = u_RoughnessFactor;
	pbrMaterial.baseColorFactor = u_BaseColorFactor;
	pbrMaterial.emissiveFactor = u_EmissiveFactor;
	pbrMaterial.exposure = u_Exposure;
	pbrMaterial.alphaCutoff = u_AlphaCutoff;
	pbrMaterial.alphaCutoffEnabled = u_AlphaCutoffEnabled;
	#ifdef MATERIAL_SPECULARGLOSSINESS
		pbrMaterial.specularFactor = u_SpecularFactor;
		pbrMaterial.diffuseFactor = u_DiffuseFactor;
		pbrMaterial.glossinessFactor = u_GlossinessFactor;
	#endif
	pbrMaterial.normalSamplerAvailable = u_NormalSamplerAvailable;
	pbrMaterial.baseColorSamplerAvailable = u_BaseColorSamplerAvailable;
	pbrMaterial.metallicRoughnessSamplerAvailable = u_MetallicRoughnessSamplerAvailable;
	pbrMaterial.normal = getNormal();
	pbrMaterial.emissiveSamplerAvailable = u_EmissiveSamplerAvailable;
	#ifdef MATERIAL_SPECULARGLOSSINESS
		pbrMaterial.specularGlossinessColor = getSpecularGlossinessColor();
	#endif
	#ifdef HAS_DIFFUSE_MAP
		pbrMaterial.diffuseColor = getDiffuseColor();
	#endif
	pbrMaterial.vertexColor = getVertexColor();
	pbrMaterial.metallicRoughnessColor = pbrMaterial.metallicRoughnessSamplerAvailable == 1?getMetallicRoughnessColor():vec4(0.0, 1.0, 1.0, 0.0);
	pbrMaterial.baseColor = pbrMaterial.baseColorSamplerAvailable == 1?getBaseColor():vec4(1.0, 1.0, 1.0, 1.0);
	pbrMaterial.emissiveColor = pbrMaterial.emissiveSamplerAvailable == 1?getEmissiveColor():vec4(0.0, 0.0, 0.0, 1.0);
	#ifdef DEBUG_NORMAL
		pbrMaterial.normalColor = getNormalColor().rgb;
	#endif
	pbrMaterial.effectColorMul = v_EffectColorMul;
	pbrMaterial.effectColorAdd = v_EffectColorAdd;

	//
	outColor = computePBRLighting(v_Position, pbrMaterial);
}

