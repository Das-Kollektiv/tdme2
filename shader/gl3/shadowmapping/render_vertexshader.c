#version 330

// based on http://fabiensanglard.net/shadowmapping/index.php, modified by me

// standard layouts
layout (location = 0) in vec3 inVertex;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureUV;

// indexed rendering
layout (location = 6) in mat4 inModelMatrix;

// uniforms
uniform mat4 projectionMatrix;
uniform mat4 cameraMatrix;
uniform mat4 depthBiasMVPMatrix;
uniform mat3 textureMatrix;
uniform vec3 lightPosition;
uniform vec3 lightDirection;

// will be passed to fragment shader
out vec2 vsFragTextureUV;
out vec4 vsShadowCoord;
out float vsShadowIntensity;
out vec3 vsPosition;

void main() {
	// pass texture uv to fragment shader
	vsFragTextureUV = vec2(textureMatrix * vec3(inTextureUV, 1.0));

	// shadow coord
	vsShadowCoord = (depthBiasMVPMatrix * inModelMatrix) * vec4(inVertex, 1.0);
	vsShadowCoord = vsShadowCoord / vsShadowCoord.w;

	// normal matrix
	mat4 normalMatrix = mat4(transpose(inverse(mat3(cameraMatrix * inModelMatrix))));

	// shadow intensity 
	vec3 normal = normalize(vec3(normalMatrix * vec4(inNormal, 0.0)));
	vsShadowIntensity = clamp(abs(dot(normalize(lightDirection.xyz), normal)), 0.0, 1.0);

	// eye coordinate position of vertex, needed in various calculations
	vec4 vsPosition4 = (cameraMatrix * inModelMatrix) * vec4(inVertex, 1.0);
	vsPosition = vsPosition4.xyz / vsPosition4.w;

	// compute gl position
	gl_Position = (projectionMatrix * cameraMatrix * inModelMatrix) * vec4(inVertex, 1.0);
	// add some bias to have DEPTHFUNCTION_LESSEQUAL working better
	gl_Position.z-= 0.0001;
}
