#version 330 core

{$DEFINITIONS}

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
	float reflection;
};

uniform Material material;

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
	#define TERRAIN_UV_SCALE			0.2
	#define TERRAIN_LEVEL_0				-4.0
	#define TERRAIN_LEVEL_1				10.0
	#define TERRAIN_HEIGHT_BLEND			4.0
	#define TERRAIN_SLOPE_BLEND			5.0

	in vec3 terrainVertex;
	in vec3 terrainNormal;
	in float terrainHeight;
	in float terrainSlope;

	uniform sampler2D grasTextureUnit;
	uniform sampler2D dirtTextureUnit;
	uniform sampler2D stoneTextureUnit;
	uniform sampler2D snowTextureUnit;

	vec4 readTerrainTextureGras(vec3 coords, vec3 blending, float scale) {
		// see: https://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
		vec4 xAxis = texture(grasTextureUnit, coords.yz * scale);
		vec4 yAxis = texture(grasTextureUnit, coords.xz * scale);
		vec4 zAxis = texture(grasTextureUnit, coords.xy * scale);
		vec4 result = xAxis * blending.x + yAxis * blending.y + zAxis * blending.z;
		return result;
	}

	vec4 readTerrainTextureDirt(vec3 coords, vec3 blending, float scale) {
		// see: https://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
		vec4 xAxis = texture(dirtTextureUnit, coords.yz * scale);
		vec4 yAxis = texture(dirtTextureUnit, coords.xz * scale);
		vec4 zAxis = texture(dirtTextureUnit, coords.xy * scale);
		vec4 result = xAxis * blending.x + yAxis * blending.y + zAxis * blending.z;
		return result;
	}

	vec4 readTerrainTextureStone(vec3 coords, vec3 blending, float scale) {
		// see: https://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
		vec4 xAxis = texture(stoneTextureUnit, coords.yz * scale);
		vec4 yAxis = texture(stoneTextureUnit, coords.xz * scale);
		vec4 zAxis = texture(stoneTextureUnit, coords.xy * scale);
		vec4 result = xAxis * blending.x + yAxis * blending.y + zAxis * blending.z;
		return result;
	}

	vec4 readTerrainTextureSnow(vec3 coords, vec3 blending, float scale) {
		// see: https://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
		vec4 xAxis = texture(snowTextureUnit, coords.yz * scale);
		vec4 yAxis = texture(snowTextureUnit, coords.xz * scale);
		vec4 zAxis = texture(snowTextureUnit, coords.xy * scale);
		vec4 result = xAxis * blending.x + yAxis * blending.y + zAxis * blending.z;
		return result;
	}

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

	// material shininess
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
		#define materialShininess material.shininess
		// see: https://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
		vec3 uvMappingBlending = abs(terrainNormal);
		uvMappingBlending = normalize(max(uvMappingBlending, 0.00001)); // Force weights to sum to 1.0
		float b = (uvMappingBlending.x + uvMappingBlending.y + uvMappingBlending.z);
		uvMappingBlending /= vec3(b, b, b);
		#if defined(HAVE_DEPTH_FOG)
			float fogStrength = 0.0;
			if (fragDepth > FOG_DISTANCE_NEAR) {
				fogStrength = (clamp(fragDepth, FOG_DISTANCE_NEAR, FOG_DISTANCE_MAX) - FOG_DISTANCE_NEAR) * 1.0 / (FOG_DISTANCE_MAX - FOG_DISTANCE_NEAR);
			}
			if (fogStrength < 1.0) {
		#endif
			vec4 terrainBlending = vec4(0.0, 0.0, 0.0, 0.0); // gras, dirt, stone, snow

			// terrainHeight
			if (terrainHeight > TERRAIN_LEVEL_1) {
				float blendFactorHeight = clamp((terrainHeight - TERRAIN_LEVEL_1) / TERRAIN_HEIGHT_BLEND, 0.0, 1.0);
				if (terrainSlope >= 45.0) {
					terrainBlending[2]+= blendFactorHeight; // stone
				} else
				if (terrainSlope >= 45.0 - TERRAIN_SLOPE_BLEND) {
					terrainBlending[2]+= blendFactorHeight * ((terrainSlope - (45.0 - TERRAIN_SLOPE_BLEND)) / TERRAIN_SLOPE_BLEND); // stone
					terrainBlending[3]+= blendFactorHeight * (1.0 - (terrainSlope - (45.0 - TERRAIN_SLOPE_BLEND)) / TERRAIN_SLOPE_BLEND); // snow
				} else {
					terrainBlending[3]+= blendFactorHeight; // snow
				}
			}
			if (terrainHeight >= TERRAIN_LEVEL_0 && terrainHeight < TERRAIN_LEVEL_1 + TERRAIN_HEIGHT_BLEND) {
				float blendFactorHeight = 1.0;
				if (terrainHeight > TERRAIN_LEVEL_1) {
					blendFactorHeight = 1.0 - clamp((terrainHeight - TERRAIN_LEVEL_1) / TERRAIN_HEIGHT_BLEND, 0.0, 1.0);
				} else
				if (terrainHeight < TERRAIN_LEVEL_0 + TERRAIN_HEIGHT_BLEND) {
					blendFactorHeight = clamp((terrainHeight - TERRAIN_LEVEL_0) / TERRAIN_HEIGHT_BLEND, 0.0, 1.0);
				}

				if (terrainSlope >= 45.0) {
					terrainBlending[2]+= blendFactorHeight; // stone
				} else
				if (terrainSlope >= 45.0 - TERRAIN_SLOPE_BLEND) {
					terrainBlending[2]+= blendFactorHeight * ((terrainSlope - (45.0 - TERRAIN_SLOPE_BLEND)) / TERRAIN_SLOPE_BLEND); // stone
					terrainBlending[1]+= blendFactorHeight * (1.0 - (terrainSlope - (45.0 - TERRAIN_SLOPE_BLEND)) / TERRAIN_SLOPE_BLEND); // dirt
				} else
				if (terrainSlope >= 26.0) {
					terrainBlending[1]+= blendFactorHeight; // dirt
				} else
				if (terrainSlope >= 26.0 - TERRAIN_SLOPE_BLEND) {
					terrainBlending[1]+= blendFactorHeight * ((terrainSlope - (26.0 - TERRAIN_SLOPE_BLEND)) / TERRAIN_SLOPE_BLEND); // dirt
					terrainBlending[0]+= blendFactorHeight * (1.0 - (terrainSlope - (26.0 - TERRAIN_SLOPE_BLEND)) / TERRAIN_SLOPE_BLEND); // gras
				} else {
					terrainBlending[0]+= blendFactorHeight; // gras
				}
			}
			if (terrainHeight < TERRAIN_LEVEL_0 + TERRAIN_HEIGHT_BLEND) {
				float blendFactorHeight = 1.0;
				if (terrainHeight > TERRAIN_LEVEL_0) {
					blendFactorHeight = 1.0 - clamp((terrainHeight - TERRAIN_LEVEL_0) / TERRAIN_HEIGHT_BLEND, 0.0, 1.0);
				}
				// 0- meter
				terrainBlending[1]+= blendFactorHeight; // dirt
			}

			//
			if (terrainBlending[0] > 0.001) diffuseTextureColor+= readTerrainTextureGras(terrainVertex, uvMappingBlending, TERRAIN_UV_SCALE) * terrainBlending[0];
			if (terrainBlending[1] > 0.001) diffuseTextureColor+= readTerrainTextureDirt(terrainVertex, uvMappingBlending, TERRAIN_UV_SCALE) * terrainBlending[1];
			if (terrainBlending[2] > 0.001) diffuseTextureColor+= readTerrainTextureStone(terrainVertex, uvMappingBlending, TERRAIN_UV_SCALE) * terrainBlending[2];
			if (terrainBlending[3] > 0.001) diffuseTextureColor+= readTerrainTextureSnow(terrainVertex, uvMappingBlending, TERRAIN_UV_SCALE) * terrainBlending[3];
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
		materialShininess = material.shininess;
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
		outMaterialShininessReflectionFragDepthType = vec4(materialShininess, material.reflection, fragDepth, 0.0);
	#else
		outMaterialShininessReflectionFragDepthType = vec4(materialShininess, material.reflection, 0.0, 0.0);
	#endif
	#if defined(HAVE_SOLID_SHADING)
		outMaterialAmbient = vec4(1.0, 1.0, 1.0, 1.0);
		outMaterialDiffuse = vec4(0.0, 0.0, 0.0, 1.0);
		outMaterialSpecular = vec4(0.0, 0.0, 0.0, 1.0);;
		outMaterialEmission = vsEffectColorAdd;
	#else
		outMaterialAmbient = material.ambient;
		outMaterialDiffuse = material.diffuse;
		outMaterialSpecular = material.specular;
		outMaterialEmission = material.emission + vsEffectColorAdd;
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
