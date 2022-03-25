#version 330 core

// uniforms
uniform sampler2D diffuseTextureUnit;
uniform int diffuseTextureAvailable;
uniform sampler2D maskTextureUnit;
uniform int maskTextureAvailable;
uniform float maskMaxValue;
uniform vec4 effectColorMul;
uniform vec4 effectColorAdd;
uniform int gradientAvailable;
uniform vec4 gradientColors[10];
uniform int gradientColorCount;
uniform float gradientColorStarts[10];

// passed from vertex shader
in vec4 vsFragColor;
flat in float vsSolidColor;
in vec2 vsFragTextureUV;
in vec2 vsFragGradientTextureUV;

// passed out
out vec4 outColor;

// main
void main(void) {
	if (maskTextureAvailable == 1) {
		vec3 maskColor = texture(maskTextureUnit, vsFragTextureUV).rgb;
		if ((maskColor.r + maskColor.g + maskColor.b) / 3.0 > maskMaxValue) discard;
	}
	if (vsSolidColor > 0.0) {
		outColor = clamp(vsFragColor, 0.0, 1.0);
	} else
	if (gradientAvailable == 1) {
		int gradientColorIdx = 0;
		for (int i = gradientColorCount - 1; i >= 0; i--) {
			if (vsFragGradientTextureUV.x > gradientColorStarts[i]) {
				gradientColorIdx = i;
				break;
			}
		}
		vec4 color = gradientColors[gradientColorIdx];
		vec4 colorNext = gradientColorIdx < gradientColorCount - 1?gradientColors[gradientColorIdx + 1]:gradientColors[gradientColorIdx];
		float colorStart = gradientColorStarts[gradientColorIdx];
		float colorStartNext = gradientColorIdx < gradientColorCount - 1?gradientColorStarts[gradientColorIdx + 1]:gradientColorStarts[gradientColorIdx];
		float colorNextBlend = clamp((vsFragGradientTextureUV.x - colorStart) / (colorStartNext - colorStart), 0.0, 1.0);
		float colorBlend = clamp(1.0 - colorNextBlend, 0.0, 1.0);
		outColor = clamp(effectColorAdd + (color * colorBlend + colorNext * colorNextBlend) * effectColorMul, 0.0, 1.0);
	} else
	if (diffuseTextureAvailable == 1) {
		outColor = clamp((effectColorAdd + texture(diffuseTextureUnit, vsFragTextureUV) * vsFragColor * effectColorMul), 0.0, 1.0);
	} else {
		outColor = clamp(effectColorAdd + vsFragColor * effectColorMul, 0.0, 1.0);
	}
}
