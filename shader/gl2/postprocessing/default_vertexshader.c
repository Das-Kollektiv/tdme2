#version 130

// layouts
attribute vec3 inVertex;
attribute vec2 inTextureUV;

// will be passed to fragment shader
varying vec2 vsFragTextureUV;

// main
void main(void) {
	// pass to fragment shader
	vsFragTextureUV = inTextureUV;

	// compute gl position
	gl_Position = vec4(inVertex, 1.0);
}
