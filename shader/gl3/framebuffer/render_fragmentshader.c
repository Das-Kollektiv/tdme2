#version 330

// uniforms
uniform sampler2D colorBufferTextureUnit;
uniform sampler2D depthBufferTextureUnit;

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

// main
void main (void) {
	outColor = texture(colorBufferTextureUnit, vsFragTextureUV);
	gl_FragDepth = texture(depthBufferTextureUnit, vsFragTextureUV).r;
}
