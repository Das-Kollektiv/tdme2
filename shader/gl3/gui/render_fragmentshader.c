#version 330

// uniforms
uniform sampler2D diffuseTextureUnit;

uniform int diffuseTextureAvailable;
uniform vec4 effectColorMul;
uniform vec4 effectColorAdd;

// passed from vertex shader
in vec4 vsFragColor;
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

// main
void main(void) {
	if (diffuseTextureAvailable == 1) {
		outColor = clamp((effectColorAdd + texture(diffuseTextureUnit, vsFragTextureUV) * vsFragColor * effectColorMul), 0.0, 1.0);
	} else {
		outColor = clamp(effectColorAdd + vsFragColor * effectColorMul, 0.0, 1.0);
	}
}
