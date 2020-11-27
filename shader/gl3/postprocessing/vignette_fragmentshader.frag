#version 330

{$DEFINITIONS}

// uniforms
uniform sampler2D colorBufferTextureUnit;
uniform sampler2D depthBufferTextureUnit;
uniform float bufferTexturePixelWidth;
uniform float bufferTexturePixelHeight;
uniform float intensity;

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

// main
void main(void) {
	float depth = texture(depthBufferTextureUnit, vsFragTextureUV).r;
	vec4 originalColor = texture(colorBufferTextureUnit, vsFragTextureUV);
	float fadeArea = intensity;
	float fragmentIntensity = 1.0;
	if (vsFragTextureUV.x < fadeArea) fragmentIntensity*= vsFragTextureUV.x / fadeArea;
	if (vsFragTextureUV.x > 1.0 - fadeArea) fragmentIntensity*= (1.0 - vsFragTextureUV.x) / fadeArea;
	if (vsFragTextureUV.y < fadeArea) fragmentIntensity*= vsFragTextureUV.y / fadeArea;
	if (vsFragTextureUV.y > 1.0 - fadeArea) fragmentIntensity*= (1.0 - vsFragTextureUV.y) / fadeArea;
	outColor = vec4(
		originalColor.r * fragmentIntensity,
		originalColor.g * fragmentIntensity,
		originalColor.b * fragmentIntensity,
		originalColor.a
	);
	gl_FragDepth = depth;
}
