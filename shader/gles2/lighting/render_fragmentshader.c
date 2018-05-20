#version 100

precision mediump float;

uniform vec4 effectColorAdd;

uniform sampler2D diffuseTextureUnit;
uniform int diffuseTextureAvailable;
uniform int diffuseTextureMaskedTransparency;
uniform float diffuseTextureMaskedTransparencyThreshold;

varying vec2 vsFragTextureUV;
varying vec4 vsFragColor;

void main (void) {
	// retrieve diffuse texture color value
	vec4 diffuseTextureColor;
	if (diffuseTextureAvailable == 1) {
		// fetch from texture
		diffuseTextureColor = texture2D(diffuseTextureUnit, vsFragTextureUV);
		// check if to handle diffuse texture masked transparency
		if (diffuseTextureMaskedTransparency == 1) {
			// discard if beeing transparent
			if (diffuseTextureColor.a < diffuseTextureMaskedTransparencyThreshold) discard;
			// set to opqaue
			diffuseTextureColor.a = 1.0;
		}
	}

	if (diffuseTextureAvailable == 1) {
		gl_FragColor = clamp(effectColorAdd + diffuseTextureColor * vsFragColor, 0.0, 1.0);
	} else {
		gl_FragColor = clamp(effectColorAdd + vsFragColor, 0.0, 1.0);
	}
}
