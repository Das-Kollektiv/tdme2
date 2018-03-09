#version 330

// based on http://fabiensanglard.net/shadowmapping/index.php, modified by me

#define SHADOWMAP_LOOKUPS	4

uniform sampler2D textureUnit;
uniform float texturePixelWidth;
uniform float texturePixelHeight;

uniform sampler2D diffuseTextureUnit;
uniform int diffuseTextureAvailable;
uniform int diffuseTextureMaskedTransparency;

uniform vec3 lightPosition;
uniform vec3 lightDirection;
uniform float lightSpotExponent;
uniform float lightSpotCosCutoff;
uniform float lightConstantAttenuation;
uniform float lightLinearAttenuation;
uniform float lightQuadraticAttenuation;

// passed from vertex shader
in vec2 vsFragTextureUV;
in vec3 vsPosition;
in vec4 vsShadowCoord;
in float vsShadowIntensity;

out vec4 outColor;

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

	// do not process samples out of frustum, or out of shadow map
	if (vsShadowCoord.w == 0.0 ||
		vsShadowCoord.x < 0.0 || vsShadowCoord.x > 1.0 ||
		vsShadowCoord.y < 0.0 || vsShadowCoord.y > 1.0) {
		// return color to be blended with framebuffer
		outColor = vec4(0.0, 0.0, 0.0, 0.0);
	} else {
		vec3 L = lightPosition - vsPosition;
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
			visibility+= texture(textureUnit, vsShadowCoord.xy + vec2(x * texturePixelWidth, y * texturePixelHeight)).x < vsShadowCoord.z + depthBias?0.40:0.0;
		}
		visibility = visibility / (SHADOWMAP_LOOKUPS * SHADOWMAP_LOOKUPS);

		// return color to be blended with framebuffer
		outColor = vec4(0.0, 0.0, 0.0, visibility * vsShadowIntensity * attenuation * 0.5);
	}
}
