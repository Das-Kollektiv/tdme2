#version 330 core

{$DEFINITIONS}

uniform sampler2D textureAtlasTextureUnit;

struct AtlasTexture {
	int orientation;
	vec2 position;
	vec2 dimension;
};

uniform AtlasTexture atlasTextures[ATLASTEXTURE_COUNT];

flat in uint vsTextureIndex;
flat in uint vsSpriteIndex;
flat in vec4 vsColor;
flat in uvec2 vsSpriteSheetDimension;
flat in vec4 vsEffectColorMul;
flat in vec4 vsEffectColorAdd;

out vec4 outColor;

#if defined(HAVE_DEPTH_FOG)
	#define FOG_DISTANCE_NEAR			100.0
	#define FOG_DISTANCE_MAX			250.0
	#define FOG_RED						(255.0 / 255.0)
	#define FOG_GREEN					(255.0 / 255.0)
	#define FOG_BLUE					(255.0 / 255.0)
	in float fragDepth;
#endif

void main(void) {
	vec2 textureCoordinate =
		gl_PointCoord / vsSpriteSheetDimension +
		vec2(
			(1.0 / float(vsSpriteSheetDimension.x)) * int(vsSpriteIndex % vsSpriteSheetDimension.x), 
			1.0 - ((1.0 / float(vsSpriteSheetDimension.y)) * int(vsSpriteIndex / vsSpriteSheetDimension.y))
		);

	// compute texture coordinate within atlas and rotate if required
	if (atlasTextures[vsTextureIndex].orientation == 2) {
		float x = textureCoordinate.x;
		textureCoordinate.x = textureCoordinate.y;
		textureCoordinate.y = x;
	}
	textureCoordinate*= atlasTextures[vsTextureIndex].dimension;
	textureCoordinate+= atlasTextures[vsTextureIndex].position;

	//
	outColor = clamp(vsEffectColorAdd + textureLod(textureAtlasTextureUnit, textureCoordinate, 0.0) * vsColor * vsEffectColorMul, 0.0, 1.0);

	#if defined(HAVE_DEPTH_FOG)
		if (fragDepth > FOG_DISTANCE_NEAR) {
			float fogStrength = (clamp(fragDepth, FOG_DISTANCE_NEAR, FOG_DISTANCE_MAX) - FOG_DISTANCE_NEAR) * 1.0 / (FOG_DISTANCE_MAX - FOG_DISTANCE_NEAR);
			outColor = vec4(
				(outColor.rgb * (1.0 - fogStrength)) +
				vec3(FOG_RED, FOG_GREEN, FOG_BLUE) * fogStrength,
				outColor.a
			);
		}
	#endif
}
