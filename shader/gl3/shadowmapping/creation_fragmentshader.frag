#version 330 core

uniform sampler2D diffuseTextureUnit;
uniform int diffuseTextureAvailable;
uniform int diffuseTextureMaskedTransparency;
uniform float diffuseTextureMaskedTransparencyThreshold;

// passed from geometry shader
in vec2 vsFragTextureUV;

uniform int textureAtlasSize;
uniform vec2 textureAtlasPixelDimension;

void main() {
	// retrieve diffuse texture color value
	if (diffuseTextureAvailable == 1) {
		// texture coordinate, also take atlas into account
		vec2 fragTextureUV;
		if (textureAtlasSize > 1) {
			#define ATLAS_TEXTURE_BORDER	32
			vec2 diffuseTextureAtlasIdx = floor(vsFragTextureUV / 1000.0);
			vec2 diffuseTextureAtlasCoord = vsFragTextureUV - 500.0 - diffuseTextureAtlasIdx * 1000.0;
			vec2 diffuseTextureAtlasTextureDimensions = vec2(1.0 / float(textureAtlasSize));
			fragTextureUV =
				mod(diffuseTextureAtlasCoord, vec2(1.0 - textureAtlasPixelDimension)) /
				float(textureAtlasSize) *
				vec2((diffuseTextureAtlasTextureDimensions - (float(ATLAS_TEXTURE_BORDER) * 2.0 * textureAtlasPixelDimension)) / diffuseTextureAtlasTextureDimensions) +
				vec2(float(ATLAS_TEXTURE_BORDER) * textureAtlasPixelDimension) +
				diffuseTextureAtlasTextureDimensions * diffuseTextureAtlasIdx;
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
