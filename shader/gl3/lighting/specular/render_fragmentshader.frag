#version 330 core

{$DEFINITIONS}

// TODO: maybe move me into definitions
struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
	float reflection;
};

{$FUNCTIONS}

uniform Material material;

uniform int textureAtlasSize;
uniform vec2 textureAtlasPixelDimension;

uniform samplerCube environmentMappingTextureUnit;
uniform int environmentMappingTextureAvailable;
uniform vec3 environmentMappingPosition;

uniform vec3 cameraPosition;

#if defined(HAVE_SOLID_SHADING)
#else
	uniform sampler2D specularTextureUnit;
	uniform int specularTextureAvailable;

	uniform sampler2D normalTextureUnit;
	uniform int normalTextureAvailable;

	// material shininess
	float materialShininess;
#endif

// passed from vertex shader
in vec2 vsFragTextureUV;
in vec3 vsNormal;
in vec3 vsPosition;
in vec3 vsTangent;
in vec3 vsBitangent;
in vec4 vsEffectColorMul;
in vec4 vsEffectColorAdd;
in vec3 vsEyeDirection;

// out
out vec4 outColor;

vec4 fragColor;

#if defined(HAVE_TERRAIN_SHADER)
	#if defined(HAVE_TERRAIN_SHADER_EDITOR)
		uniform int brushEnabled;
		uniform vec2 brushPosition;
		uniform vec2 brushTextureDimension;
		uniform sampler2D brushTextureUnit;
		uniform mat3 brushTextureMatrix;
	#endif
#elif defined(HAVE_WATER_SHADER)
#else
	uniform sampler2D diffuseTextureUnit;
	uniform int diffuseTextureAvailable;
	uniform int diffuseTextureMaskedTransparency;
	uniform float diffuseTextureMaskedTransparencyThreshold;
#endif

#if defined(HAVE_DEPTH_FOG)
	#define FOG_DISTANCE_NEAR			100.0
	#define FOG_DISTANCE_MAX				250.0
	#define FOG_RED						(255.0 / 255.0)
	#define FOG_GREEN					(255.0 / 255.0)
	#define FOG_BLUE						(255.0 / 255.0)
	in float fragDepth;
#endif

void main(void) {
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
	#if defined(HAVE_TERRAIN_SHADER)
	#elif defined(HAVE_WATER_SHADER)
	#else
		vec4 diffuseTextureColor;
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
	#endif

	//
	fragColor = vec4(0.0, 0.0, 0.0, 0.0);
	fragColor+= clamp(material.emission, 0.0, 1.0);

	#if defined(HAVE_SOLID_SHADING)
		fragColor+= material.ambient;
		// no op
	#else
		vec3 normal = vsNormal;

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
		if (normalTextureAvailable == 1) {
			vec3 normalVector = normalize(texture(normalTextureUnit, fragTextureUV).rgb * 2.0 - 1.0);
			normal = vec3(0.0, 0.0, 0.0);
			normal+= vsTangent * normalVector.x;
			normal+= vsBitangent * normalVector.y;
			normal+= vsNormal * normalVector.z;
		}

		// compute lights
		fragColor+= computeSpecularLights(normal, vsPosition, vsEyeDirection, material);

		// reflection
		#if defined(HAVE_WATER_SHADER)
		#else
			if (material.reflection > 0.0 && environmentMappingTextureAvailable == 1) {
				vec3 reflectionVector = reflect(normalize(vsPosition.xyz - environmentMappingPosition), normal);
				#if defined(__VULKAN__)
					reflectionVector*= vec3(1.0, -1.0, 1.0);
				#endif
				fragColor+= texture(environmentMappingTextureUnit, -reflectionVector) * material.reflection;
			}
		#endif
	#endif

	// take effect colors into account
	fragColor*= vsEffectColorMul;
	fragColor.a = material.diffuse.a * vsEffectColorMul.a;

	#if defined(HAVE_DEPTH_FOG)
		float fogStrength = 0.0;
		if (fragDepth > FOG_DISTANCE_NEAR) {
			fogStrength = (clamp(fragDepth, FOG_DISTANCE_NEAR, FOG_DISTANCE_MAX) - FOG_DISTANCE_NEAR) * 1.0 / (FOG_DISTANCE_MAX - FOG_DISTANCE_NEAR);
		}
	#endif

	//
	#if defined(HAVE_TERRAIN_SHADER)
		if (fogStrength < 1.0) {
			outColor = vsEffectColorAdd;
			outColor+= computeTerrainTexture(terrainVertex, terrainNormal);
			outColor*= fragColor;
			#if defined(HAVE_TERRAIN_SHADER_EDITOR)
				if (brushEnabled == 1) {
					vec2 brushTextureUV = vec2(brushTextureMatrix * vec3(((vsPosition.xz - brushPosition) / brushTextureDimension), 1.0));
					if (brushTextureUV.x >= 0.0 && brushTextureUV.x < 1.0 &&
						brushTextureUV.y >= 0.0 && brushTextureUV.y < 1.0) {
						outColor+= vec4(texture(brushTextureUnit, brushTextureUV).rgb * 0.25, 0.0);
					}
				}
			#endif
			outColor = clamp(outColor, 0.0, 1.0);
			if (fogStrength > 0.0) {
				outColor = vec4(
					(outColor.rgb * (1.0 - fogStrength)) +
					vec3(FOG_RED, FOG_GREEN, FOG_BLUE) * fogStrength,
					1.0
				);
			}
		} else {
			outColor = vec4(
				vec3(FOG_RED, FOG_GREEN, FOG_BLUE) * fogStrength,
				1.0
			);
		}
	#elif defined(HAVE_WATER_SHADER)
		//
		vec4 envColor = vec4(0.2, 0.2, 0.6, 1.0);
		if (environmentMappingTextureAvailable == 1) {
			vec3 reflectionVector = reflect(normalize(vsPosition - cameraPosition), normalize(normal * vec3(0.01, 1.0, 0.01)));
			#if defined(__VULKAN__)
				reflectionVector*= vec3(1.0, -1.0, 1.0);
			#endif
			envColor = texture(environmentMappingTextureUnit, reflectionVector);
		}
		outColor = fragColor * 0.4;
		outColor+= envColor;
		outColor+= vsEffectColorAdd;
		outColor = clamp(outColor, 0.0, 1.0);
		outColor.a = 0.6;
		if (fogStrength > 0.0) {
			outColor = vec4(
				(outColor.rgb * (1.0 - fogStrength)) +
				vec3(FOG_RED, FOG_GREEN, FOG_BLUE) * fogStrength,
				0.6
			);
		}
	#else
		if (diffuseTextureAvailable == 1) {
			outColor = clamp((vsEffectColorAdd + diffuseTextureColor) * fragColor, 0.0, 1.0);
		} else {
			outColor = clamp(vsEffectColorAdd + fragColor, 0.0, 1.0);
		}
		if (outColor.a < 0.0001) discard;
		#if defined(HAVE_BACK)
			gl_FragDepth = 1.0;
		#endif
		#if defined(HAVE_FRONT)
			gl_FragDepth = 0.0;
		#endif
		#if defined(HAVE_DEPTH_FOG)
			if (fogStrength > 0.0) {
				outColor = vec4(
					(outColor.rgb * (1.0 - fogStrength)) +
					vec3(FOG_RED, FOG_GREEN, FOG_BLUE) * fogStrength,
					1.0
				);
			}
		#endif
	#endif
}
