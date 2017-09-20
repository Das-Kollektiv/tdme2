// based on http://fabiensanglard.net/shadowmapping/index.php, modified by me

#version 120

uniform mat4 depthBiasMVPMatrix;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 normalMatrix;
uniform vec3 lightPosition;
uniform vec3 lightDirection;

varying vec4 vsShadowCoord;
varying float vsShadowIntensity;
varying vec3 vsPosition;

void main() {
	// shadow coord
	vsShadowCoord = depthBiasMVPMatrix * gl_Vertex;
	vsShadowCoord = vsShadowCoord / vsShadowCoord.w;

	// shadow intensity 
	vec3 normal = normalize(vec3(normalMatrix * vec4(gl_Normal, 0.0)));
	vsShadowIntensity = clamp(abs(dot(normalize(lightDirection.xyz), normal)), 0.0, 1.0);

	// Eye-coordinate position of vertex, needed in various calculations
	vec4 vsPosition4 = mvMatrix * gl_Vertex;
	vsPosition = vsPosition4.xyz / vsPosition4.w;

	// compute gl position
	gl_Position = mvpMatrix * gl_Vertex;
}
