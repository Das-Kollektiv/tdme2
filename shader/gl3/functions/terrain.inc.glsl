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

vec4 computeTerrainTexture(vec3 vertex, vec3 normal) {
	// see: https://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
	vec3 uvMappingBlending = abs(normal);
	uvMappingBlending = normalize(max(uvMappingBlending, 0.00001)); // Force weights to sum to 1.0
	float b = (uvMappingBlending.x + uvMappingBlending.y + uvMappingBlending.z);
	uvMappingBlending /= vec3(b, b, b);

	//
	vec4 result = vec4(0.0, 0.0, 0.0, 0.0);
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
	if (terrainBlending[0] > 0.001) result+= readTerrainTextureGras(vertex, uvMappingBlending, TERRAIN_UV_SCALE) * terrainBlending[0];
	if (terrainBlending[1] > 0.001) result+= readTerrainTextureDirt(vertex, uvMappingBlending, TERRAIN_UV_SCALE) * terrainBlending[1];
	if (terrainBlending[2] > 0.001) result+= readTerrainTextureStone(vertex, uvMappingBlending, TERRAIN_UV_SCALE) * terrainBlending[2];
	if (terrainBlending[3] > 0.001) result+= readTerrainTextureSnow(vertex, uvMappingBlending, TERRAIN_UV_SCALE) * terrainBlending[3];

	//
	return result;
}
