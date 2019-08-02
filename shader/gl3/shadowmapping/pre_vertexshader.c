#version 330

// standard layouts
layout (location = 0) in vec3 inVertex;
layout (location = 2) in vec2 inTextureUV;

// indexed rendering
layout (location = 6) in mat4 inModelMatrix;

// uniforms
uniform mat4 cameraMatrix;
uniform mat4 projectionMatrix;
uniform mat3 textureMatrix;

{$DEFINITIONS}

#if defined(HAVE_GEOMETRY_SHADER)
	// will be passed to geometry shader
	out vec2 vsFragTextureUV;
	out mat4 vsModelMatrix;
#else
	// will be passed to fragment shader
	out vec2 gsFragTextureUV;

	#define vsFragTextureUV inTextureUV
	#define vsModelMatrix inModelMatrix

	#define GS_IN_ARRAY_AT(array, index) array
#endif

{$FUNCTIONS}

void main() {
	#if defined(HAVE_GEOMETRY_SHADER)
		// pass to geometry shader
		vsFragTextureUV = inTextureUV;
		vsModelMatrix = inModelMatrix;
		// position
		gl_Position = vec4(inVertex, 1.0);
	#else
		// compute vertex and pass to fragment shader
		computeVertex(vec4(inVertex, 1.0), -1, mat4(1.0));
	#endif
}
