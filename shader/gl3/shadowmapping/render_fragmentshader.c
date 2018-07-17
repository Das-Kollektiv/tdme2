#version 330

// based on http://fabiensanglard.net/shadowmapping/index.php, modified by me

#define SHADOWMAP_LOOKUPS	4

// uniforms
uniform sampler2D textureUnit;
uniform float texturePixelWidth;
uniform float texturePixelHeight;

uniform sampler2D diffuseTextureUnit;
uniform int diffuseTextureAvailable;
uniform int diffuseTextureMaskedTransparency;
uniform float diffuseTextureMaskedTransparencyThreshold;

uniform vec3 lightPosition;
uniform vec3 lightDirection;
uniform float lightSpotExponent;
uniform float lightSpotCosCutoff;
uniform float lightConstantAttenuation;
uniform float lightLinearAttenuation;
uniform float lightQuadraticAttenuation;

// passed from geometry shader
in vec2 gsFragTextureUV;
in vec3 gsPosition;
in vec4 gsShadowCoord;
in float gsShadowIntensity;

// fragment color
out vec4 outColor;

void main() {
	// retrieve diffuse texture color value
	if (diffuseTextureAvailable == 1) {
		// fetch from texture
		vec4 diffuseTextureColor = texture(diffuseTextureUnit, gsFragTextureUV);
		// check if to handle diffuse texture masked transparency
		if (diffuseTextureMaskedTransparency == 1) {
			// discard if beeing transparent
			if (diffuseTextureColor.a < diffuseTextureMaskedTransparencyThreshold) discard;
		}
	}

	// do not process samples out of frustum, or out of shadow map
	if (gsShadowCoord.w == 0.0 ||
		gsShadowCoord.x < 0.0 || gsShadowCoord.x > 1.0 ||
		gsShadowCoord.y < 0.0 || gsShadowCoord.y > 1.0) {
		// return color to be blended with framebuffer
		outColor = vec4(0.0, 0.0, 0.0, 0.0);
	} else {
		vec3 L = lightPosition - gsPosition;
		float d = length(L);
		L = normalize(L);

		// compute attenuation
		float attenuation =
			1.0 /
			(
				lightConstantAttenuation +
				lightLinearAttenuation * d +
				lightQuadraticAttenuation * d * d
			);
	 
		// see if point on surface is inside cone of illumination
		float spotDot = dot(-L, normalize(lightDirection));
		float spotAttenuation = 0.0;
		if (spotDot >= lightSpotCosCutoff) {
			spotAttenuation = pow(spotDot, lightSpotExponent);
		}

		// Combine the spotlight and distance attenuation.
		attenuation *= spotAttenuation;

		// depth bias
		float depthBias = 0.0;

		// determine visibility
		float visibility = 0.0;
		for (float y = -SHADOWMAP_LOOKUPS / 2; y <= SHADOWMAP_LOOKUPS / 2; y+=1.0)
		for (float x = -SHADOWMAP_LOOKUPS / 2; x <= SHADOWMAP_LOOKUPS / 2; x+=1.0) {
			visibility+= texture(textureUnit, gsShadowCoord.xy + vec2(x * texturePixelWidth, y * texturePixelHeight)).x < gsShadowCoord.z + depthBias?0.40:0.0;
		}
		visibility = visibility / (SHADOWMAP_LOOKUPS * SHADOWMAP_LOOKUPS);

		// return color to be blended with framebuffer
		outColor = vec4(0.0, 0.0, 0.0, visibility * gsShadowIntensity * attenuation * 0.5);
	}
}
