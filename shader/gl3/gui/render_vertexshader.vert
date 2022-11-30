#version 330 core

// layout
layout (location = 0) in vec2 inVertex;
layout (location = 1) in float inSolidColor;
layout (location = 2) in vec2 inTextureUV;
layout (location = 3) in vec4 inColor;

// uniforms
uniform mat3 textureMatrix;
uniform mat3 inverseGradientTextureMatrix;

// will be passed to fragment shader
out vec4 vsFragColor;
flat out float vsSolidColor;
out vec2 vsFragTextureUV;
out vec2 vsFragGradientTextureUV;

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
