#version 330 core

{$DEFINITIONS}

#define FALSE		0
#define MAX_LIGHTS	8

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
	float reflection;
};

struct Light {
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

uniform Light lights[MAX_LIGHTS];

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

uniform float bufferTexturePixelWidth;
uniform float bufferTexturePixelHeight;

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

// terrain
#define TERRAIN_UV_SCALE			0.2
#define TERRAIN_LEVEL_0				-4.0
#define TERRAIN_LEVEL_1				10.0
#define TERRAIN_HEIGHT_BLEND			4.0
#define TERRAIN_SLOPE_BLEND			5.0

uniform sampler2D grasTextureUnit;
uniform sampler2D dirtTextureUnit;
uniform sampler2D stoneTextureUnit;
uniform sampler2D snowTextureUnit;

vec4 readTerrainTextureGras(vec3 coords, vec3 blending, vec2 dPdx1, vec2 dPdy1, vec2 dPdx2, vec2 dPdy2, vec2 dPdx3, vec2 dPdy3) {
	// see: https://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
	vec4 xAxis = textureGrad(grasTextureUnit, coords.yz, dPdx1, dPdy1);
	vec4 yAxis = textureGrad(grasTextureUnit, coords.xz, dPdx2, dPdy2);
	vec4 zAxis = textureGrad(grasTextureUnit, coords.xy, dPdx3, dPdy3);
	vec4 result = xAxis * blending.x + yAxis * blending.y + zAxis * blending.z;
	return result;
}

vec4 readTerrainTextureDirt(vec3 coords, vec3 blending, vec2 dPdx1, vec2 dPdy1, vec2 dPdx2, vec2 dPdy2, vec2 dPdx3, vec2 dPdy3) {
	// see: https://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
	vec4 xAxis = textureGrad(dirtTextureUnit, coords.yz, dPdx1, dPdy1);
	vec4 yAxis = textureGrad(dirtTextureUnit, coords.xz, dPdx2, dPdy2);
	vec4 zAxis = textureGrad(dirtTextureUnit, coords.xy, dPdx3, dPdy3);
	vec4 result = xAxis * blending.x + yAxis * blending.y + zAxis * blending.z;
	return result;
}

vec4 readTerrainTextureStone(vec3 coords, vec3 blending, vec2 dPdx1, vec2 dPdy1, vec2 dPdx2, vec2 dPdy2, vec2 dPdx3, vec2 dPdy3) {
	// see: https://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
	vec4 xAxis = textureGrad(stoneTextureUnit, coords.yz, dPdx1, dPdy1);
	vec4 yAxis = textureGrad(stoneTextureUnit, coords.xz, dPdx2, dPdy2);
	vec4 zAxis = textureGrad(stoneTextureUnit, coords.xy, dPdx3, dPdy3);
	vec4 result = xAxis * blending.x + yAxis * blending.y + zAxis * blending.z;
	return result;
}

vec4 readTerrainTextureSnow(vec3 coords, vec3 blending, vec2 dPdx1, vec2 dPdy1, vec2 dPdx2, vec2 dPdy2, vec2 dPdx3, vec2 dPdy3) {
	// see: https://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
	vec4 xAxis = textureGrad(snowTextureUnit, coords.yz, dPdx1, dPdy1);
	vec4 yAxis = textureGrad(snowTextureUnit, coords.xz, dPdx2, dPdy2);
	vec4 zAxis = textureGrad(snowTextureUnit, coords.xy, dPdx3, dPdy3);
	vec4 result = xAxis * blending.x + yAxis * blending.y + zAxis * blending.z;
	return result;
}

vec3 getTerrainUVMappingBlending(vec3 normal) {
	vec3 uvMappingBlending = abs(normal);
	uvMappingBlending = normalize(max(uvMappingBlending, 0.00001)); // Force weights to sum to 1.0
	float b = (uvMappingBlending.x + uvMappingBlending.y + uvMappingBlending.z);
	uvMappingBlending /= vec3(b, b, b);
	return uvMappingBlending;
}

#if defined(HAVE_DEPTH_FOG)
	#define FOG_DISTANCE_NEAR			100.0
	#define FOG_DISTANCE_MAX				250.0
	#define FOG_RED						(255.0 / 255.0)
	#define FOG_GREEN					(255.0 / 255.0)
	#define FOG_BLUE						(255.0 / 255.0)
#endif

//
vec4 computeLight(in int i, in vec3 normal, in vec3 position, in Material material) {
	vec3 vsEyeDirection = normalize(vec3(cameraMatrix * -vec4(position, 0.0)));
	vec3 lightDirection = lights[i].position.xyz - position.xyz;
	float lightDistance = length(lightDirection);
	lightDirection = normalize(lightDirection);
	vec3 reflectionDirection = normalize(reflect(-lightDirection, normal));

	// compute attenuation
	float lightAttenuation =
		1.0 /
		(
			lights[i].constantAttenuation +
			lights[i].linearAttenuation * lightDistance +
			lights[i].quadraticAttenuation * lightDistance * lightDistance
		);

	// see if point on surface is inside cone of illumination
	float lightSpotDot = dot(-lightDirection, normalize(lights[i].spotDirection));
	float lightSpotAttenuation = 0.0;
	if (lightSpotDot >= lights[i].spotCosCutoff) {
		lightSpotAttenuation = pow(lightSpotDot, lights[i].spotExponent);
	}

	// Combine the spotlight and distance attenuation.
	lightAttenuation *= lightSpotAttenuation;

	// add color components to fragment color
	return
		clamp(lights[i].ambient * material.ambient, 0.0, 1.0) +
		clamp(lights[i].diffuse * material.diffuse * max(dot(normal, lightDirection), 0.0) * lightAttenuation, 0.0, 1.0) +
		clamp(lights[i].specular * material.specular * pow(max(dot(reflectionDirection, vsEyeDirection), 0.0), 0.3 * material.shininess) * lightAttenuation, 0.0, 1.0);
}

//
vec4 computeLights(in vec3 normal, in vec3 position, in Material material) {
	vec4 fragColor = vec4(0.0, 0.0, 0.0, 0.0);
	// process each light
	for (int i = 0; i < MAX_LIGHTS; i++) {
		// skip on disabled lights
		if (lights[i].enabled == FALSE || (lights[i].radius > 0.0 && length(lights[i].position.xyz - position.xyz) > lights[i].radius)) continue;

		// compute light
		fragColor+= computeLight(i, normal, position, material);
	}
	//
	return fragColor;
}

// main
void main(void) {
	outColor = vec4(1.0, 0.0, 0.0, 1.0);
	Material material;
	material.diffuse = texture(colorBufferTextureUnit2, vsFragTextureUV).rgba;
	if (material.diffuse.a < 0.001) discard;
	vec4 shininessReflectionFragDepthType = texture(geometryBufferTextureId3, vsFragTextureUV).xyzw;
	float fragDepth = shininessReflectionFragDepthType.z;
	material.ambient = texture(colorBufferTextureUnit1, vsFragTextureUV).rgba;
	material.specular = texture(colorBufferTextureUnit3, vsFragTextureUV).rgba;
	material.emission = texture(colorBufferTextureUnit4, vsFragTextureUV).rgba;
	vec3 position = texture(geometryBufferTextureId1, vsFragTextureUV).xyz;
	vec3 normal = texture(geometryBufferTextureId2, vsFragTextureUV).xyz;
	int type = int(shininessReflectionFragDepthType.w);
	vec4 diffuse = texture(colorBufferTextureUnit5, vsFragTextureUV).rgba;
	#if defined(HAVE_DEPTH_FOG)
		float fogStrength = 0.0;
		if (fragDepth > FOG_DISTANCE_NEAR) {
			fogStrength = (clamp(fragDepth, FOG_DISTANCE_NEAR, FOG_DISTANCE_MAX) - FOG_DISTANCE_NEAR) * 1.0 / (FOG_DISTANCE_MAX - FOG_DISTANCE_NEAR);
		}
	#endif
	if (type == 0) {
		material.shininess = shininessReflectionFragDepthType.x;
		material.reflection = shininessReflectionFragDepthType.y;
	} else
	if (type == 1) {
		//
		material.shininess = 0.0;
		material.reflection = 0.0;
		//
		float terrainHeight = shininessReflectionFragDepthType.x;
		float terrainSlope = shininessReflectionFragDepthType.y;
		// see: https://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
		vec3 uvMappingBlending = getTerrainUVMappingBlending(normal);
		vec3 nxPosition = texture(geometryBufferTextureId1, vsFragTextureUV + vec2(bufferTexturePixelWidth, 0.0)).xyz;
		vec3 nyPosition = texture(geometryBufferTextureId1, vsFragTextureUV + vec2(0.0, bufferTexturePixelHeight)).xyz;
		//
		vec4 terrainColor = vec4(0.0, 0.0, 0.0, 1.0);
		#if defined(HAVE_DEPTH_FOG)
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
			vec2 dPdx1 = (nxPosition.yz - position.yz) * TERRAIN_UV_SCALE;
			vec2 dPdy1 = (nyPosition.yz - position.yz) * TERRAIN_UV_SCALE;
			vec2 dPdx2 = (nxPosition.xz - position.xz) * TERRAIN_UV_SCALE;
			vec2 dPdy2 = (nyPosition.xz - position.xz) * TERRAIN_UV_SCALE;
			vec2 dPdx3 = (nxPosition.xy - position.xy) * TERRAIN_UV_SCALE;
			vec2 dPdy3 = (nyPosition.xy - position.xy) * TERRAIN_UV_SCALE;
			if (terrainBlending[0] > 0.001) terrainColor+= readTerrainTextureGras(position * TERRAIN_UV_SCALE, uvMappingBlending, dPdx1, dPdy1, dPdx2, dPdy2, dPdx3, dPdy3) * terrainBlending[0];
			if (terrainBlending[1] > 0.001) terrainColor+= readTerrainTextureDirt(position * TERRAIN_UV_SCALE, uvMappingBlending, dPdx1, dPdy1, dPdx2, dPdy2, dPdx3, dPdy3) * terrainBlending[1];
			if (terrainBlending[2] > 0.001) terrainColor+= readTerrainTextureStone(position * TERRAIN_UV_SCALE, uvMappingBlending, dPdx1, dPdy1, dPdx2, dPdy2, dPdx3, dPdy3) * terrainBlending[2];
			if (terrainBlending[3] > 0.001) terrainColor+= readTerrainTextureSnow(position * TERRAIN_UV_SCALE, uvMappingBlending, dPdx1, dPdy1, dPdx2, dPdy2, dPdx3, dPdy3) * terrainBlending[3];
			diffuse*= terrainColor;
		#if defined(HAVE_DEPTH_FOG)
			}
		#endif
	}
	vec4 fragColor = material.emission + computeLights(normal, position, material);
	outColor = clamp(fragColor * diffuse, 0.0, 1.0);
	outColor.a = material.diffuse.a;
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
