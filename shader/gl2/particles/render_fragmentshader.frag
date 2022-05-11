#version 100

precision highp float;
precision highp sampler2D;

{$DEFINITIONS}

uniform sampler2D textureAtlasTextureUnit;

struct AtlasTexture {
	int orientation;
	vec2 position;
	vec2 dimension;
};

uniform AtlasTexture atlasTextures[ATLASTEXTURE_COUNT];

varying float vsTextureIndex;
varying float vsSpriteIndex;
varying vec4 vsColor;
varying vec2 vsSpriteSheetDimension;
varying vec4 vsEffectColorMul;
varying vec4 vsEffectColorAdd;

void main(void) {
	vec2 textureCoordinate =
		gl_PointCoord / floor(vsSpriteSheetDimension) +
		vec2(
			(1.0 / floor(vsSpriteSheetDimension.x)) * floor(mod(floor(vsSpriteIndex), floor(vsSpriteSheetDimension.x))),
			1.0 - ((1.0 / floor(vsSpriteSheetDimension.y)) * floor(floor(vsSpriteIndex) / floor(vsSpriteSheetDimension.y)))
		);
	int textureIndex = int(vsTextureIndex);

	// compute texture coordinate within atlas and rotate if required
	if (atlasTextures[textureIndex].orientation == 2) {
		float x = textureCoordinate.x;
		textureCoordinate.x = textureCoordinate.y;
		textureCoordinate.y = x;
	}
	textureCoordinate*= atlasTextures[textureIndex].dimension;
	textureCoordinate+= atlasTextures[textureIndex].position;

	//
	gl_FragColor = clamp(vsEffectColorAdd + texture2D(textureAtlasTextureUnit, textureCoordinate, 0.0) * vsColor * vsEffectColorMul, 0.0, 1.0);
}
