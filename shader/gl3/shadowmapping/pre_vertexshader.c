#version 330

// standard layouts
layout (location = 0) in vec3 inVertex;
layout (location = 2) in vec2 inTextureUV;

// indexed rendering
layout (location = 6) in mat4 inModelMatrix;

// render groups
layout (location = 12) in vec3 inOrigin;

// uniforms
uniform mat4 cameraMatrix;
uniform mat4 projectionMatrix;
uniform mat3 textureMatrix;
uniform int frame;

{$DEFINITIONS}

// will be passed to fragment shader
out vec2 vsFragTextureUV;

{$FUNCTIONS}

void main() {
	#if defined(HAVE_TREE)
		mat4 shaderTransformMatrix = createTreeTransformMatrix(inOrigin, inVertex, vec3(inModelMatrix[3][0], inModelMatrix[3][1], inModelMatrix[3][2]));
	#elif defined(HAVE_FOLIAGE)
		mat4 shaderTransformMatrix = createFoliageTransformMatrix(inOrigin, inVertex, vec3(inModelMatrix[3][0], inModelMatrix[3][1], inModelMatrix[3][2]));
	#else
		mat4 shaderTransformMatrix = mat4(1.0);
	#endif

	// compute vertex and pass to fragment shader
	computeVertex(vec4(inVertex, 1.0), shaderTransformMatrix);
}
