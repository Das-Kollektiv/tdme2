#version 330

// standard layouts
layout (location = 0) in vec3 inVertex;
layout (location = 2) in vec2 inTextureUV;

// indexed rendering
layout (location = 6) in mat4 inModelMatrix;

// will be passed to geometry shader
out vec2 vsFragTextureUV;
out mat4 vsModelMatrix;

// uniforms
uniform mat3 textureMatrix;

void main() {
	// pass to geometry shader
	vsFragTextureUV = vec2(textureMatrix * vec3(inTextureUV, 1.0));
	vsModelMatrix = inModelMatrix;

	// position
	gl_Position = vec4(inVertex, 1.0);
}
