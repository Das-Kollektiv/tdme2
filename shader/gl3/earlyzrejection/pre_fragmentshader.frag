#version 330

uniform sampler2D diffuseTextureUnit;
uniform int diffuseTextureAvailable;
uniform int diffuseTextureMaskedTransparency;
uniform float diffuseTextureMaskedTransparencyThreshold;

uniform int textureAtlasSize;
uniform vec2 textureAtlasPixelDimension;

// passed from geometry shader
in vec2 vsFragTextureUV;

void main() {
	// retrieve diffuse texture color value
	if (diffuseTextureAvailable == 1) {
		// texture coordinate, also take atlas into account
		vec2 fragTextureUV;
		if (textureAtlasSize > 1) {
			#define ATLAS_TEXTURE_BORDER	8
			vec2 diffuseTextureAtlasIdx = floor(vsFragTextureUV / 1000.0);
			vec2 diffuseTextureAtlasCoord = vsFragTextureUV - 500.0 - diffuseTextureAtlasIdx * 1000.0;
			fragTextureUV = mod(diffuseTextureAtlasCoord, 1.0 - textureAtlasPixelDimension * float(ATLAS_TEXTURE_BORDER * 2) * float(textureAtlasSize)) / float(textureAtlasSize) + diffuseTextureAtlasIdx / float(textureAtlasSize) + textureAtlasPixelDimension * ATLAS_TEXTURE_BORDER;
		} else {
			fragTextureUV = vsFragTextureUV;
		}
		// fetch from texture
		vec4 diffuseTextureColor = texture(diffuseTextureUnit, fragTextureUV);
		// check if to handle diffuse texture masked transparency
		if (diffuseTextureMaskedTransparency == 1) {
			// discard if beeing transparent
			if (diffuseTextureColor.a < diffuseTextureMaskedTransparencyThreshold) discard;
		}
	}
}
