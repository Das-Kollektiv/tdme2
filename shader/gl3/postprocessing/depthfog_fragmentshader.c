#version 330

// uniforms
uniform sampler2D colorBufferTextureUnit;
uniform sampler2D depthBufferTextureUnit;
uniform float bufferTexturePixelWidth;
uniform float bufferTexturePixelHeight;

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

#define DISTANCE_NEAR		0.99
#define DISTANCE_MAX		1.0

// main
void main (void) {
	outColor = texture(colorBufferTextureUnit, vsFragTextureUV);
	gl_FragDepth = texture(depthBufferTextureUnit, vsFragTextureUV).r;
	if (gl_FragDepth > DISTANCE_NEAR) {
		float fogStrength = (clamp(gl_FragDepth, DISTANCE_NEAR, DISTANCE_MAX) - DISTANCE_NEAR) * 1.0 / (DISTANCE_MAX - DISTANCE_NEAR);
		outColor = vec4(
			(outColor.rgb * (1.0 - fogStrength)) +
			vec3(1.0, 1.0, 1.0) * fogStrength,
			outColor.a
		);
	}
}
