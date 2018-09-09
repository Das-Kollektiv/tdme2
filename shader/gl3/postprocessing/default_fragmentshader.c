#version 330

#define SHADOWMAP_LOOKUPS_NEAR		4
#define SHADOWMAP_LOOKUPS_FAR		8

// uniforms
uniform sampler2D colorBufferTextureUnit;
uniform sampler2D depthBufferTextureUnit;
uniform float bufferTexturePixelWidth;
uniform float bufferTexturePixelHeight;

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

// main
void main (void) {
	outColor = texture(colorBufferTextureUnit, vsFragTextureUV);
}
