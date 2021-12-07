#version 330 core

// TODO: maybe move me into definitions
#if !defined(HAVE_SPECULARMATERIAL_STRUCT)
#define HAVE_SPECULARMATERIAL_STRUCT
struct SpecularMaterial {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
	float reflection;
};
#endif

#if !defined(HAVE_SPECULARLIGHT_STRUCT)
#define HAVE_SPECULARLIGHT_STRUCT
struct SpecularLight {
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
	float radius;
};
#endif

{$DEFINITIONS}

{$FUNCTIONS}

uniform SpecularMaterial specularMaterial;

// passed from vertex shader
in vec2 vsFragTextureUV;
in vec3 vsNormal;
in vec3 vsPosition;
in vec3 vsTangent;
in vec3 vsBitangent;
in vec4 vsEffectColorMul;
in vec4 vsEffectColorAdd;
in vec3 vsEyeDirection;

#if defined(HAVE_TERRAIN_SHADER)
	#if defined(HAVE_TERRAIN_SHADER_EDITOR)
		uniform int brushEnabled;
		uniform vec2 brushPosition;
		uniform vec2 brushTextureDimension;
		uniform sampler2D brushTextureUnit;
		uniform mat3 brushTextureMatrix;
	#endif
#else
	uniform sampler2D diffuseTextureUnit;
	uniform int diffuseTextureAvailable;
	uniform int diffuseTextureMaskedTransparency;
	uniform float diffuseTextureMaskedTransparencyThreshold;

	uniform int textureAtlasSize;
	uniform vec2 textureAtlasPixelDimension;

	uniform sampler2D specularTextureUnit;
	uniform int specularTextureAvailable;

	uniform sampler2D normalTextureUnit;
	uniform int normalTextureAvailable;

	// specularMaterial shininess
	float materialShininess;
#endif

#if defined(HAVE_DEPTH_FOG)
	#define FOG_DISTANCE_NEAR			100.0
	#define FOG_DISTANCE_MAX				250.0
	#define FOG_RED						(255.0 / 255.0)
	#define FOG_GREEN					(255.0 / 255.0)
	#define FOG_BLUE						(255.0 / 255.0)
	in float fragDepth;
#endif

// out
layout (location = 0) out vec3 outPosition;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec4 outMaterialShininessReflectionFragDepthType;
layout (location = 3) out vec4 outMaterialAmbient;
layout (location = 4) out vec4 outMaterialDiffuse;
layout (location = 5) out vec4 outMaterialSpecular;
layout (location = 6) out vec4 outMaterialEmission;
layout (location = 7) out vec4 outDiffuse;

void main(void) {
	#if defined(HAVE_TERRAIN_SHADER)
		vec4 diffuseTextureColor = vec4(0.0, 0.0, 0.0, 1.0);
		#define normal terrainNormal
		#define materialShininess specularMaterial.shininess
		#if defined(HAVE_DEPTH_FOG)
			float fogStrength = 0.0;
			if (fragDepth > FOG_DISTANCE_NEAR) {
				fogStrength = (clamp(fragDepth, FOG_DISTANCE_NEAR, FOG_DISTANCE_MAX) - FOG_DISTANCE_NEAR) * 1.0 / (FOG_DISTANCE_MAX - FOG_DISTANCE_NEAR);
			}
			if (fogStrength < 1.0) {
		#endif
			diffuseTextureColor+= computeTerrainTexture(terrainVertex, terrainNormal);
			#if defined(HAVE_TERRAIN_SHADER_EDITOR)
				if (brushEnabled == 1) {
					vec2 brushTextureUV = vec2(brushTextureMatrix * vec3(((vsPosition.xz - brushPosition) / brushTextureDimension), 1.0));
					if (brushTextureUV.x >= 0.0 && brushTextureUV.x < 1.0 &&
						brushTextureUV.y >= 0.0 && brushTextureUV.y < 1.0) {
						diffuseTextureColor+= vec4(texture(brushTextureUnit, brushTextureUV).rgb * 0.25, 0.0);
					}
				}
			#endif
		#if defined(HAVE_DEPTH_FOG)
			}
		#endif
	#else
		// texture coordinate, also take atlas into account
		vec2 fragTextureUV;
		if (textureAtlasSize > 1) {
			#define ATLAS_TEXTURE_BORDER	32
			vec2 diffuseTextureAtlasIdx = floor(vsFragTextureUV / 1000.0);
			vec2 diffuseTextureAtlasCoord = vsFragTextureUV - 500.0 - diffuseTextureAtlasIdx * 1000.0;
			vec2 diffuseTextureAtlasTextureDimensions = vec2(1.0 / float(textureAtlasSize));
			fragTextureUV =
				mod(diffuseTextureAtlasCoord, vec2(1.0 - textureAtlasPixelDimension)) /
				float(textureAtlasSize) *
				vec2((diffuseTextureAtlasTextureDimensions - (float(ATLAS_TEXTURE_BORDER) * 2.0 * textureAtlasPixelDimension)) / diffuseTextureAtlasTextureDimensions) +
				vec2(float(ATLAS_TEXTURE_BORDER) * textureAtlasPixelDimension) +
				diffuseTextureAtlasTextureDimensions * diffuseTextureAtlasIdx;
		} else {
			fragTextureUV = vsFragTextureUV;
		}

		// diffuse texture color
		vec4 diffuseTextureColor = vec4(1.0, 1.0, 1.0, 1.0);
		if (diffuseTextureAvailable == 1) {
			diffuseTextureColor = texture(diffuseTextureUnit, fragTextureUV);
			// check if to handle diffuse texture masked transparency
			if (diffuseTextureMaskedTransparency == 1) {
				// discard if beeing transparent
				if (diffuseTextureColor.a < diffuseTextureMaskedTransparencyThreshold) discard;
				// set to opqaue
				diffuseTextureColor.a = 1.0;
			}
		}

		// specular
		materialShininess = specularMaterial.shininess;
		if (specularTextureAvailable == 1) {
			vec3 specularTextureValue = texture(specularTextureUnit, fragTextureUV).rgb;
			materialShininess =
				((0.33 * specularTextureValue.r) +
				(0.33 * specularTextureValue.g) +
				(0.33 * specularTextureValue.b)) * 255.0;
		}
	
		// compute normal
		vec3 normal = vsNormal;
		if (normalTextureAvailable == 1) {
			vec3 normalVector = normalize(texture(normalTextureUnit, fragTextureUV).rgb * 2.0 - 1.0);
			normal = vec3(0.0, 0.0, 0.0);
			normal+= vsTangent * normalVector.x;
			normal+= vsBitangent * normalVector.y;
			normal+= vsNormal * normalVector.z;
		}
	#endif

	//
	outPosition = vsPosition;
	outNormal = normal;
	#if defined(HAVE_DEPTH_FOG)
		outMaterialShininessReflectionFragDepthType = vec4(materialShininess, specularMaterial.reflection, fragDepth, 0.0);
	#else
		outMaterialShininessReflectionFragDepthType = vec4(materialShininess, specularMaterial.reflection, 0.0, 0.0);
	#endif
	#if defined(HAVE_SOLID_SHADING)
		outMaterialAmbient = vec4(1.0, 1.0, 1.0, 1.0);
		outMaterialDiffuse = vec4(0.0, 0.0, 0.0, 1.0);
		outMaterialSpecular = vec4(0.0, 0.0, 0.0, 1.0);;
		outMaterialEmission = vsEffectColorAdd;
	#else
		outMaterialAmbient = specularMaterial.ambient;
		outMaterialDiffuse = specularMaterial.diffuse;
		outMaterialSpecular = specularMaterial.specular;
		outMaterialEmission = specularMaterial.emission + vsEffectColorAdd;
	#endif
	outDiffuse = diffuseTextureColor * vsEffectColorMul;

	//
	#if defined(HAVE_BACK)
		gl_FragDepth = 1.0;
	#endif
	#if defined(HAVE_FRONT)
		gl_FragDepth = 0.0;
	#endif
}
