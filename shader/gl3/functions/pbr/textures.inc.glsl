in vec2 v_UVCoord1;
in vec2 v_UVCoord2;

// general material
uniform int u_NormalSamplerAvailable;
uniform sampler2D u_NormalSampler;
uniform float u_NormalScale;
in mat3 v_TBN;

// emissive
uniform int u_EmissiveSamplerAvailable;
uniform sampler2D u_EmissiveSampler;

#ifdef HAS_OCCLUSION_MAP
uniform sampler2D u_OcclusionSampler;
uniform int u_OcclusionUVSet;
uniform float u_OcclusionStrength;
uniform mat3 u_OcclusionUVTransform;
#endif

// Metallic Roughness Material
uniform int u_BaseColorSamplerAvailable;
uniform sampler2D u_BaseColorSampler;

uniform int u_MetallicRoughnessSamplerAvailable;
uniform sampler2D u_MetallicRoughnessSampler;

// Specular Glossiness Material
#ifdef HAS_DIFFUSE_MAP
uniform sampler2D u_DiffuseSampler;
uniform int u_DiffuseUVSet;
uniform mat3 u_DiffuseUVTransform;
#endif

#ifdef HAS_SPECULAR_GLOSSINESS_MAP
uniform sampler2D u_SpecularGlossinessSampler;
uniform int u_SpecularGlossinessUVSet;
uniform mat3 u_SpecularGlossinessUVTransform;
#endif

vec2 getNormalUV()
{
    return v_UVCoord1;
}

vec4 getNormalColor()
{
    return texture(u_NormalSampler, getNormalUV());
}

// Find the normal for this fragment, pulling either from a predefined normal map
// or from the interpolated mesh normal and tangent attributes.
vec3 getNormal()
{
    vec2 UV = getNormalUV();

    // Retrieve the tangent space matrix
    mat3 tbn = v_TBN;

    vec3 n;
    if (u_NormalSamplerAvailable == 1) {
        n = texture(u_NormalSampler, UV).rgb;
        n = normalize(tbn * ((2.0 * n - 1.0) * vec3(u_NormalScale, u_NormalScale, 1.0)));
    } else {
        // The tbn matrix is linearly interpolated, so we need to re-normalize
        n = normalize(tbn[2].xyz);
    }
    return n;
}

vec2 getEmissiveUV()
{
	return v_UVCoord1;
}

vec4 getEmissiveColor()
{
	if (u_EmissiveSamplerAvailable == 1) {
		return texture(u_EmissiveSampler, getEmissiveUV());
	} else {
		return vec4(0.0);
	}
}

#ifdef HAS_OCCLUSION_MAP
vec2 getOcclusionUV()
{
    vec3 uv = vec3(v_UVCoord1, 1.0);
    uv.xy = u_OcclusionUVSet < 1 ? v_UVCoord1 : v_UVCoord2;
    #ifdef HAS_OCCLSION_UV_TRANSFORM
    uv *= u_OcclusionUVTransform;
    #endif
    return uv.xy;
}

vec4 getOcclusionColor()
{
	return texture(u_OcclusionSampler,  getOcclusionUV());
}
#endif

vec2 getBaseColorUV()
{
    return v_UVCoord1;
}

vec4 getBaseColor()
{
    return texture(u_BaseColorSampler, getBaseColorUV());
}

vec2 getMetallicRoughnessUV()
{
    return v_UVCoord1;
}

vec4 getMetallicRoughnessColor()
{
    return texture(u_MetallicRoughnessSampler, getMetallicRoughnessUV());
}

#ifdef HAS_SPECULAR_GLOSSINESS_MAP
vec2 getSpecularGlossinessUV()
{
    vec3 uv = vec3(v_UVCoord1, 1.0);
    uv.xy = u_SpecularGlossinessUVSet < 1 ? v_UVCoord1 : v_UVCoord2;
    #ifdef HAS_SPECULARGLOSSINESS_UV_TRANSFORM
    uv *= u_SpecularGlossinessUVTransform;
    #endif
    return uv.xy;
}

vec4 getSpecularGlossinessColor() {
	return texture(u_SpecularGlossinessSampler, getSpecularGlossinessUV());
}
#endif

#ifdef HAS_DIFFUSE_MAP
vec2 getDiffuseUV()
{
    vec3 uv = vec3(v_UVCoord1, 1.0);
    uv.xy = u_DiffuseUVSet < 1 ? v_UVCoord1 : v_UVCoord2;
    #ifdef HAS_DIFFUSE_UV_TRANSFORM
    uv *= u_DiffuseUVTransform;
    #endif
    return uv.xy;
}

vec4 getDiffuseColor()
{
	return texture(u_DiffuseSampler, getDiffuseUV());
}
#endif
