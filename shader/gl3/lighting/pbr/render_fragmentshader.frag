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

uniform float u_MetallicFactor;
uniform float u_RoughnessFactor;
uniform vec4 u_BaseColorFactor;
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
	#ifdef MATERIAL_SPECULARGLOSSINESS
		pbrMaterial.specularGlossinessColor = getSpecularGlossinessColor();
	#endif
	#ifdef HAS_DIFFUSE_MAP
		pbrMaterial.diffuseColor = getDiffuseColor();
	#endif
	pbrMaterial.vertexColor = getVertexColor();
	pbrMaterial.metallicRoughnessColor = pbrMaterial.metallicRoughnessSamplerAvailable == 1?getMetallicRoughnessColor():vec4(0.0, 1.0, 1.0, 0.0);
	pbrMaterial.baseColor = pbrMaterial.baseColorSamplerAvailable == 1?getBaseColor():vec4(1.0, 1.0, 1.0, 1.0);
	#ifdef DEBUG_NORMAL
		pbrMaterial.normalColor = getNormalColor().rgb;
	#endif

	//
	outColor = computePBRLighting(v_Position, pbrMaterial);
}

