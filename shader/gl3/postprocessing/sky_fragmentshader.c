#version 330

// uniforms
uniform sampler2D colorBufferTextureUnit;
uniform sampler2D depthBufferTextureUnit;
uniform sampler2D temporaryColorBufferTextureUnit;
uniform sampler2D temporaryDepthBufferTextureUnit;
uniform float bufferTexturePixelWidth;
uniform float bufferTexturePixelHeight;

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

// main
void main (void) {
	float fragDepth = texture(depthBufferTextureUnit, vsFragTextureUV).r;
	outColor = fragDepth < 1.0?texture(colorBufferTextureUnit, vsFragTextureUV):texture(temporaryColorBufferTextureUnit, vsFragTextureUV);
	gl_FragDepth = fragDepth;
}
