#version 330 core

// layout
layout (location = 0) in vec3 inVertex;
layout (location = 2) in vec2 inTextureUV;

// will be passed to fragment shader
out vec2 vsFragTextureUV;

// main
void main(void) {
	// pass to fragment shader
	vsFragTextureUV = inTextureUV;
	gl_Position = vec4(inVertex, 1.0);
}
