// based on http://fabiensanglard.net/shadowmapping/index.php, modified by me

#version 100

precision highp float;

#define SHADOWMAP_LOOKUPS	2.0

uniform sampler2D textureUnit;
uniform float texturePixelWidth;
uniform float texturePixelHeight;

uniform vec3 lightDirection;

varying vec3 vsPosition;
varying vec4 vsShadowCoord;
varying float vsShadowIntensity;

void main() {
	// do not process samples out of frustum
	if (vsShadowCoord.w == 0.0) {
		// return color to be blended with framebuffer
		gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
	} else {
		// depth bias
		float depthBias = 0.0;

		// determine visibility
		float visibility = 0.0;
		for (float y = (-SHADOWMAP_LOOKUPS + 0.5) / 2.0; y <= (+SHADOWMAP_LOOKUPS - 0.5) / 2.0; y+=1.0)
		for (float x = (-SHADOWMAP_LOOKUPS + 0.5) / 2.0; x <= (+SHADOWMAP_LOOKUPS - 0.5) / 2.0; x+=1.0) {
			visibility+= texture2D(textureUnit, vsShadowCoord.xy + vec2(x * texturePixelWidth, y * texturePixelHeight)).z < vsShadowCoord.z + depthBias?0.40:0.0;
		}
		visibility = visibility / (SHADOWMAP_LOOKUPS * SHADOWMAP_LOOKUPS);

		// return color to be blended with framebuffer
		gl_FragColor = vec4(0.0, 0.0, 0.0, visibility * vsShadowIntensity * 0.5);
	}
}
