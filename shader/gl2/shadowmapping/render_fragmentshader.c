// based on http://fabiensanglard.net/shadowmapping/index.php, modified by me

#version 120

#define SHADOWMAP_LOOKUPS	4

uniform sampler2D textureUnit;
uniform float texturePixelWidth;
uniform float texturePixelHeight;

uniform vec3 lightPosition;
uniform vec3 lightDirection;
uniform float lightSpotExponent;
uniform float lightSpotCosCutoff;
uniform float lightConstantAttenuation;
uniform float lightLinearAttenuation;
uniform float lightQuadraticAttenuation;

varying vec3 vsPosition;
varying vec4 vsShadowCoord;
varying float vsShadowIntensity;

void main() {
	// do not process samples out of frustum
	if (vsShadowCoord.w == 0.0) {
		// return color to be blended with framebuffer
		gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
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
		for (float y = (-SHADOWMAP_LOOKUPS + 0.5) / 2; y <= (+SHADOWMAP_LOOKUPS - 0.5) / 2; y+=1.0)
		for (float x = (-SHADOWMAP_LOOKUPS + 0.5) / 2; x <= (+SHADOWMAP_LOOKUPS - 0.5) / 2; x+=1.0) {
			visibility+= texture2D(textureUnit, vsShadowCoord.xy + vec2(x * texturePixelWidth, y * texturePixelHeight)).z <= vsShadowCoord.z + depthBias?0.4:0.0;
		}
		visibility = visibility / (SHADOWMAP_LOOKUPS * SHADOWMAP_LOOKUPS);

		// return color to be blended with framebuffer
		gl_FragColor = vec4(0.0, 0.0, 0.0, visibility * vsShadowIntensity * attenuation * 0.5);
	}
}
