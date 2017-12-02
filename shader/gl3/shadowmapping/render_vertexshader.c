#version 330

precision highp float;
precision highp int;
precision highp sampler2D;

// based on http://fabiensanglard.net/shadowmapping/index.php, modified by me

layout (location = 0) in vec3 inVertex;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureUV;

uniform mat4 depthBiasMVPMatrix;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 normalMatrix;
uniform vec3 lightPosition;
uniform vec3 lightDirection;

// will be passed to fragment shader
out vec2 vsFragTextureUV;
out vec4 vsShadowCoord;
out float vsShadowIntensity;
out vec3 vsPosition;

void main() {
	// pass texture uv to fragment shader
	vsFragTextureUV = inTextureUV;

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
