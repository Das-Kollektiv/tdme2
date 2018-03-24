#version 330

// standard layouts
layout (location = 0) in vec3 inVertex;
layout (location = 2) in vec2 inTextureUV;

// indexed rendering
layout (location = 6) in mat4 inModelMatrix;

// uniforms
uniform mat4 projectionMatrix;
uniform mat4 cameraMatrix;

// will be passed to fragment shader
out vec2 vsFragTextureUV;

void main(){
	// pass texture uv to fragment shader
	vsFragTextureUV = inTextureUV;

	// position
	gl_Position = (projectionMatrix * cameraMatrix * inModelMatrix) * vec4(inVertex, 1.0);
}
