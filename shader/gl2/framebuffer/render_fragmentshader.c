#version 120

// uniforms
uniform sampler2D diffuseTextureUnit;

// passed from vertex shader
varying vec2 vsFragTextureUV;

// main
void main (void) {
	gl_FragColor = texture2D(diffuseTextureUnit, vsFragTextureUV);
}
