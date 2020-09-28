#version 100

precision highp float;
precision highp sampler2D;

uniform sampler2D diffuseTextureUnits[48];

varying float vsTextureIndex;
varying float vsSpriteIndex;
varying vec4 vsColor;
varying vec2 vsSpriteSheetDimension;
varying vec4 vsEffectColorMul;
varying vec4 vsEffectColorAdd;

void main(void) {
	vec2 spriteCoord = gl_PointCoord / ivec2(vsSpriteSheetDimension) + vec2((1.0 / float(int(vsSpriteSheetDimension.x))) * float(mod(int(vsSpriteIndex), 4)), 1.0 - ((1.0 / float(int(vsSpriteSheetDimension.y))) * float(int(vsSpriteIndex) / 4)));
	gl_FragColor = clamp(vsEffectColorAdd + texture2D(diffuseTextureUnits[int(vsTextureIndex)], spriteCoord) * vsColor * vsEffectColorMul, 0.0, 1.0);
}
