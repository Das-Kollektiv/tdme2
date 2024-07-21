#version 330 core

// uniforms
uniform sampler2D colorBufferTextureUnit;
uniform sampler2D depthBufferTextureUnit;

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

// main
void main(void) {
	vec4 c = texture(colorBufferTextureUnit, vsFragTextureUV);
	outColor.r = (c.r - 0.9) * 10.0;
	outColor.g = c.g;
	outColor.b = c.b;
	outColor.a = 1.0;
	gl_FragDepth = texture(depthBufferTextureUnit, vsFragTextureUV).r;
}
