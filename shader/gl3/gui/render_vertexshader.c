#version 330

// layout
layout (location = 0) in vec3 inVertex;
layout (location = 2) in vec2 inTextureUV;
layout (location = 3) in vec4 inColor;

// will be passed to fragment shader
out vec4 vsFragColor;
out vec2 vsFragTextureUV;

// main
void main(void) {
	// pass to fragment shader
	vsFragColor = inColor;
	vsFragTextureUV = inTextureUV;

	// compute gl position
	gl_Position = vec4(inVertex, 1.0);
}
