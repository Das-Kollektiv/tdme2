#version 100

precision mediump float;

uniform sampler2D diffuseTextureUnit;
uniform vec4 effectColorMul;
uniform vec4 effectColorAdd;

varying vec4 fragColor;

void main (void) {
	gl_FragColor = clamp(effectColorAdd + texture2D(diffuseTextureUnit, gl_PointCoord) * fragColor * effectColorMul, 0.0, 1.0);
}
