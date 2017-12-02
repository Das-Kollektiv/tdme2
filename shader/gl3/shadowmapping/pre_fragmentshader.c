#version 330

precision highp float;
precision highp int;
precision highp sampler2D;

uniform sampler2D diffuseTextureUnit;
uniform int diffuseTextureAvailable;
uniform int diffuseTextureMaskedTransparency;

// passed from vertex shader
in vec2 vsFragTextureUV;

void main() {
	// retrieve diffuse texture color value
	if (diffuseTextureAvailable == 1) {
		// fetch from texture
		vec4 diffuseTextureColor = texture(diffuseTextureUnit, vsFragTextureUV);
		// check if to handle diffuse texture masked transparency
		if (diffuseTextureMaskedTransparency == 1) {
			// discard if beeing transparent
			if (diffuseTextureColor.a < 0.1) discard;
		}
	}
}
