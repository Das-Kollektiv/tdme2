#version 330

#define MAP_LOOKUPS_NEAR		4
#define MAP_LOOKUPS_FAR		8

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
	float depth = texture(depthBufferTextureUnit, vsFragTextureUV).r;
	vec3 originalColor = texture(colorBufferTextureUnit, vsFragTextureUV).rgb;
	vec3 blurredColor = vec3(0.0, 0.0, 0.0);
	outColor = vec4(originalColor, 1.0);
	if (depth > 0.96) {
		float intensity = clamp((depth - 0.96) * 1.0 / (0.98 - 0.96), 0.0, 1.0);
		for (int y = 0; y < MAP_LOOKUPS_NEAR; y++)
		for (int x = 0; x < MAP_LOOKUPS_NEAR; x++) {
			blurredColor+= texture(
				colorBufferTextureUnit,
				vsFragTextureUV.xy +
					vec2(
						(-MAP_LOOKUPS_NEAR / 2.0 + 0.5 + x) * bufferTexturePixelWidth,
						(-MAP_LOOKUPS_NEAR / 2.0 + 0.5 + y) * bufferTexturePixelHeight
					)
			).rgb;
		}
		blurredColor/= MAP_LOOKUPS_NEAR * MAP_LOOKUPS_NEAR;
		blurredColor*= intensity;
		blurredColor+= originalColor * (1.0 - intensity);
		outColor = vec4(blurredColor, 1.0);
	}
	if (depth > 0.98) {
		originalColor = blurredColor;
		blurredColor = vec3(0.0, 0.0, 0.0);
		float intensity = clamp((depth - 0.98) * 1.0 / (0.985 - 0.98), 0.0, 1.0);
		for (int y = 0; y < MAP_LOOKUPS_FAR; y++)
		for (int x = 0; x < MAP_LOOKUPS_FAR; x++) {
			blurredColor+= texture(
				colorBufferTextureUnit,
				vsFragTextureUV.xy +
					vec2(
						(-MAP_LOOKUPS_FAR / 2.0 + 0.5 + x) * bufferTexturePixelWidth,
						(-MAP_LOOKUPS_FAR / 2.0 + 0.5 + y) * bufferTexturePixelHeight
					)
			).rgb;
		}
		blurredColor/= MAP_LOOKUPS_FAR * MAP_LOOKUPS_FAR;
		blurredColor*= intensity;
		blurredColor+= originalColor * (1.0 - intensity);
		outColor = vec4(blurredColor, 1.0);
	}
	gl_FragDepth = depth;
}
