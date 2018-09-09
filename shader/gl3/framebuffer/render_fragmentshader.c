#version 330

// uniforms
uniform sampler2D diffuseTextureUnit;

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

// main
void main (void) {
	outColor = texture(diffuseTextureUnit, vsFragTextureUV);
}
