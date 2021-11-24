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

void main()
{
	MaterialProperties materialProperties;
	materialProperties.metallicFactor = u_MetallicFactor;
	materialProperties.roughnessFactor = u_RoughnessFactor;
	materialProperties.baseColorFactor = u_BaseColorFactor;
	materialProperties.exposure = u_Exposure;
	materialProperties.alphaCutoff = u_AlphaCutoff;
	materialProperties.alphaCutoffEnabled = u_AlphaCutoffEnabled;
	#ifdef MATERIAL_SPECULARGLOSSINESS
		materialProperties.specularFactor = u_SpecularFactor;
		materialProperties.diffuseFactor = u_DiffuseFactor;
		materialProperties.glossinessFactor = u_GlossinessFactor;
	#endif
	materialProperties.normalSamplerAvailable = u_NormalSamplerAvailable;
	materialProperties.baseColorSamplerAvailable = u_BaseColorSamplerAvailable;
	materialProperties.metallicRoughnessSamplerAvailable = u_MetallicRoughnessSamplerAvailable;
	materialProperties.normal = getNormal();
	#ifdef MATERIAL_SPECULARGLOSSINESS
		materialProperties.specularGlossinessColor = getSpecularGlossinessColor();
	#endif
	#ifdef HAS_DIFFUSE_MAP
		materialProperties.diffuseColor = getDiffuseColor();
	#endif
	materialProperties.vertexColor = getVertexColor();
	materialProperties.metallicRoughnessColor = materialProperties.metallicRoughnessSamplerAvailable == 1?getMetallicRoughnessColor():vec4(0.0, 1.0, 1.0, 0.0);
	materialProperties.baseColor = materialProperties.baseColorSamplerAvailable == 1?getBaseColor():vec4(1.0, 1.0, 1.0, 1.0);
	#ifdef DEBUG_NORMAL
		materialProperties.normalColor = getNormalColor().rgb;
	#endif

	//
	outColor = computePBRLighting(materialProperties);
};

