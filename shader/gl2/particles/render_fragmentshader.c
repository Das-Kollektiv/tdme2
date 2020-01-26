#version 100

precision mediump float;

uniform sampler2D diffuseTextureUnit;
uniform vec4 effectColorMul;
uniform vec4 effectColorAdd;
uniform int spritesHorizontal;
uniform int spritesVertical;

varying float vsSpriteIndex;
varying vec4 vsFragColor;

void main (void) {
	vec2 spriteCoord = (gl_PointCoord / vec2(spritesHorizontal, spritesVertical)) + vec2((1.0 / float(spritesHorizontal)) * mod(vsSpriteIndex, 4.0), 1.0 - ((1.0 / float(spritesHorizontal)) * floor(vsSpriteIndex / 4.0)));
	gl_FragColor = clamp(effectColorAdd + texture2D(diffuseTextureUnit, spriteCoord) * vsFragColor * effectColorMul, 0.0, 1.0);
}
