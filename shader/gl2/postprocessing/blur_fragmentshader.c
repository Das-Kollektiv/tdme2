#version 120

#define SHADOWMAP_LOOKUPS_NEAR		4
#define SHADOWMAP_LOOKUPS_FAR		8

// uniforms
uniform sampler2D colorBufferTextureUnit;
uniform sampler2D depthBufferTextureUnit;
uniform float bufferTexturePixelWidth;
uniform float bufferTexturePixelHeight;

// passed from vertex shader
varying vec2 vsFragTextureUV;

// main
void main (void) {
	float depth = texture2D(depthBufferTextureUnit, vsFragTextureUV).z;
	vec3 originalColor = texture2D(colorBufferTextureUnit, vsFragTextureUV).xyz;
	vec3 blurredColor;
	gl_FragColor = vec4(originalColor, 1.0);
	if (depth > 0.96) {
		float intensity = clamp((depth - 0.96) * 1.0 / (0.98 - 0.96), 0.0, 1.0);
		for (float y = -SHADOWMAP_LOOKUPS_NEAR / 2; y < SHADOWMAP_LOOKUPS_NEAR / 2; y+=1.0)
		for (float x = -SHADOWMAP_LOOKUPS_NEAR / 2; x < SHADOWMAP_LOOKUPS_NEAR / 2; x+=1.0) {
			blurredColor+= texture2D(colorBufferTextureUnit, vsFragTextureUV.xy + vec2(x * bufferTexturePixelWidth, y * bufferTexturePixelHeight)).xyz;
		}
		blurredColor/= SHADOWMAP_LOOKUPS_NEAR * SHADOWMAP_LOOKUPS_NEAR;
		blurredColor*= intensity;
		blurredColor+= originalColor * (1.0 - intensity);
		gl_FragColor = vec4(blurredColor, 1.0);
	}
	if (depth > 0.98) {
		originalColor = blurredColor;
		blurredColor = vec3(0.0, 0.0, 0.0);
		float intensity = clamp((depth - 0.98) * 1.0 / (1.0 - 0.98), 0.0, 1.0);
		for (float y = -SHADOWMAP_LOOKUPS_FAR / 2; y < SHADOWMAP_LOOKUPS_FAR / 2; y+=1.0)
		for (float x = -SHADOWMAP_LOOKUPS_FAR / 2; x < SHADOWMAP_LOOKUPS_FAR / 2; x+=1.0) {
			blurredColor+= texture2D(colorBufferTextureUnit, vsFragTextureUV.xy + vec2(x * bufferTexturePixelWidth, y * bufferTexturePixelHeight)).xyz;
		}
		blurredColor/= SHADOWMAP_LOOKUPS_FAR * SHADOWMAP_LOOKUPS_FAR;
		blurredColor*= intensity;
		blurredColor+= originalColor * (1.0 - intensity);
		gl_FragColor = vec4(blurredColor, 1.0);
	}
}
