#version 100

// layouts
attribute vec3 inVertex;
attribute vec2 inTextureUV;
attribute vec4 inColor;

// uniforms
uniform mat3 textureMatrix;

// will be passed to fragment shader
varying vec4 vsFragColor;
varying vec2 vsFragTextureUV;

// main
void main(void) {
	// pass to fragment shader
	vsFragColor = inColor;
	vsFragTextureUV = vec2(textureMatrix * vec3(inTextureUV, 1.0));

	// compute gl position
	gl_Position = vec4(inVertex, 1.0);
}
