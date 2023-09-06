#version 100

// layouts
attribute vec2 inVertex;
attribute float inSolidColor;
attribute vec2 inTextureUV;
attribute vec4 inColor;

// uniforms
uniform mat3 textureMatrix;
uniform mat3 inverseGradientTextureMatrix;

// will be passed to fragment shader
varying vec4 vsFragColor;
varying float vsSolidColor;
varying vec2 vsFragTextureUV;
varying vec2 vsFragGradientTextureUV;

// main
void main(void) {
	// pass to fragment shader
	vsFragColor = inColor;
	vsSolidColor = inSolidColor;
	vsFragTextureUV = vec2(textureMatrix * vec3(inTextureUV, 1.0));
	vsFragGradientTextureUV = vec2(inverseGradientTextureMatrix * vec3(inTextureUV, 1.0));

	// compute gl position
	gl_Position = vec4(vec3(inVertex, 0.0), 1.0);
}
