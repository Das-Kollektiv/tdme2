#version 330

// uniforms
//layout(binding = 2) uniform sampler2D diffuseTextureUnit;

uniform int diffuseTextureAvailable;
uniform int padding1;
uniform int padding2;
uniform int padding3;
uniform vec4 effectColorMul;
uniform vec4 effectColorAdd;

{$UNIFORMS}

// passed from vertex shader
layout (location = 0) in vec4 vsFragColor;
layout (location = 1) in vec2 vsFragTextureUV;

// passed out
layout (location = 0) out vec4 outColor;

// main
void main (void) {
//	if (diffuseTextureAvailable == 1) {
//		// outColor = clamp((effectColorAdd + texture(diffuseTextureUnit, vsFragTextureUV) * vsFragColor * effectColorMul), 0.0, 1.0);
//		outColor = vec4(0.0, 0.0, 1.0, 1.0);
//	} else {
		outColor = clamp(effectColorAdd + vsFragColor * effectColorMul, 0.0, 1.0);
//	}
}
