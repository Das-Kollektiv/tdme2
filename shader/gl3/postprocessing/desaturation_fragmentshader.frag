#version 330

{$DEFINITIONS}

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
void main(void) {
	float depth = texture(depthBufferTextureUnit, vsFragTextureUV).r;
	vec4 originalColor = texture(colorBufferTextureUnit, vsFragTextureUV);
	outColor = vec4(
		(originalColor.r + originalColor.g + originalColor.b) / 3.0,   
		(originalColor.r + originalColor.g + originalColor.b) / 3.0,
		(originalColor.r + originalColor.g + originalColor.b) / 3.0,
		originalColor.a
	);
	gl_FragDepth = depth;
}
