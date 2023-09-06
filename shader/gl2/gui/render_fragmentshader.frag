#version 100

precision mediump float;

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
varying vec4 vsFragColor;
varying float vsSolidColor;
varying vec2 vsFragTextureUV;
varying vec2 vsFragGradientTextureUV;

// main
void main (void) {
	if (maskTextureAvailable == 1) {
		vec3 maskColor = texture2D(maskTextureUnit, vsFragTextureUV).rgb;
		if ((maskColor.r + maskColor.g + maskColor.b) / 3.0 > maskMaxValue) discard;
	}
	if (vsSolidColor > 0.0) {
		gl_FragColor = clamp(vsFragColor, 0.0, 1.0);
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
		gl_FragColor = color * colorBlend + colorNext * colorNextBlend;
	} else
	if (diffuseTextureAvailable == 1) {
		gl_FragColor = clamp((effectColorAdd + (texture2D(diffuseTextureUnit, vsFragTextureUV)) * vsFragColor * effectColorMul), 0.0, 1.0);
	} else {
		gl_FragColor = clamp(effectColorAdd + vsFragColor, 0.0, 1.0);
	}
}
