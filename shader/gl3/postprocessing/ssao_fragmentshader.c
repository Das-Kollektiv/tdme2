#version 330

{$DEFINITIONS}

#if defined(HAVE_4K)
	#define SSAO_MAP_LOOKUPS		4
#else
	#define SSAO_MAP_LOOKUPS		2
#endif

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
	float depth = texture(depthBufferTextureUnit, vsFragTextureUV).r;
	vec3 originalColor = texture(colorBufferTextureUnit, vsFragTextureUV).rgb;

	// scale with SSAO color
	outColor = vec4(originalColor, 1.0);
	vec3 ssaoColor = vec3(0.0, 0.0, 0.0);
	for (int y = 0; y < SSAO_MAP_LOOKUPS; y++)
	for (int x = 0; x < SSAO_MAP_LOOKUPS; x++) {
		ssaoColor+= texture(
			temporaryColorBufferTextureUnit,
			vsFragTextureUV.xy +
				vec2(
					(-SSAO_MAP_LOOKUPS / 2.0 + 0.5 + x) * bufferTexturePixelWidth,
					(-SSAO_MAP_LOOKUPS / 2.0 + 0.5 + y) * bufferTexturePixelHeight
				)
		).rgb;
	}
	ssaoColor/= SSAO_MAP_LOOKUPS * SSAO_MAP_LOOKUPS;
	outColor*= vec4(ssaoColor, 1.0);

	gl_FragDepth = depth;
}
