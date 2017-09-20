#version 100

precision mediump float;

// uniforms
uniform sampler2D diffuseTextureUnit;
uniform int diffuseTextureAvailable;
uniform vec4 effectColorMul;
uniform vec4 effectColorAdd;

// passed from vertex shader
varying vec2 vsFragTextureUV;
varying vec4 vsFragColor;

// main
void main (void) {
	//
	if (diffuseTextureAvailable == 1) {
		gl_FragColor = clamp((effectColorAdd + (texture2D(diffuseTextureUnit, vsFragTextureUV)) * vsFragColor * effectColorMul), 0.0, 1.0);
	} else {
		gl_FragColor = clamp(effectColorAdd + vsFragColor, 0.0, 1.0);
	}
}
