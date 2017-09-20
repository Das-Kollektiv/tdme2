#version 100

precision mediump float;

uniform sampler2D diffuseTextureUnit;
uniform int diffuseTextureAvailable;
uniform vec4 effectColorAdd;

varying vec2 fragTextureUV;
varying vec4 fragColor;
varying vec4 outColor;

void main (void) {
	if (diffuseTextureAvailable == 1) {
		gl_FragColor = clamp((effectColorAdd + (texture2D(diffuseTextureUnit, fragTextureUV)) * fragColor), 0.0, 1.0);
	} else {
		gl_FragColor = clamp(effectColorAdd + fragColor, 0.0, 1.0);
	}
}
