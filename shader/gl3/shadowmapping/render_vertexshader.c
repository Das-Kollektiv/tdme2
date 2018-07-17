#version 330

// based on http://fabiensanglard.net/shadowmapping/index.php, modified by me

// standard layouts
layout (location = 0) in vec3 inVertex;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureUV;

// indexed rendering
layout (location = 6) in mat4 inModelMatrix;

// will be passed to fragment shader
out vec2 vsFragTextureUV;
out vec3 vsNormal;
out mat4 vsModelMatrix;

// uniforms
uniform mat3 textureMatrix;

void main() {
	// pass to geometry shader
	vsFragTextureUV = vec2(textureMatrix * vec3(inTextureUV, 1.0));
	vsNormal = inNormal;
	vsModelMatrix = inModelMatrix;
	gl_Position = vec4(inVertex, 1.0);
}
