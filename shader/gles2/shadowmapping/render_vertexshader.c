// based on http://fabiensanglard.net/shadowmapping/index.php, modified by me

#version 100

precision highp float;

attribute vec3 inVertex;
attribute vec3 inNormal;
attribute vec2 inTextureUV;

uniform mat4 depthBiasMVPMatrix;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 normalMatrix;
uniform vec3 lightDirection;

varying vec4 vsShadowCoord;
varying float vsShadowIntensity;
varying vec3 vsPosition;

void main() {
	// shadow coord
	vsShadowCoord = depthBiasMVPMatrix * vec4(inVertex, 1.0);
	vsShadowCoord = vsShadowCoord / vsShadowCoord.w;

	// shadow intensity 
	vec3 normal = normalize(vec3(normalMatrix * vec4(inNormal, 0.0)));
	vsShadowIntensity = clamp(abs(dot(normalize(lightDirection.xyz), normal)), 0.0, 1.0);

	// Eye-coordinate position of vertex, needed in various calculations
	vec4 vsPosition4 = mvMatrix * vec4(inVertex, 1.0);
	vsPosition = vsPosition4.xyz / vsPosition4.w;

	// compute gl position
	gl_Position = mvpMatrix * vec4(inVertex, 1.0);
}
