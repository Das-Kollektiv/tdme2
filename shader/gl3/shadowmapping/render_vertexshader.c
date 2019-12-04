#version 330

// based on http://fabiensanglard.net/shadowmapping/index.php, modified by me

// standard layouts
layout (location = 0) in vec3 inVertex;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureUV;

// indexed rendering
layout (location = 6) in mat4 inModelMatrix;

// render groups
layout (location = 12) in vec3 inOrigin;

// uniforms
uniform mat4 projectionMatrix;
uniform mat4 cameraMatrix;
uniform mat4 depthBiasMVPMatrix;
uniform vec3 lightPosition;
uniform vec3 lightDirection;
uniform mat3 textureMatrix;
uniform int frame;

{$DEFINITIONS}

// will be passed to fragment shader
out vec2 vsFragTextureUV;
out vec4 vsShadowCoord;
out float vsShadowIntensity;
out vec3 vsPosition;

{$FUNCTIONS}

void main() {
	#if defined(HAVE_FOLIAGE)
		mat4 shaderTransformMatrix = createFoliageTransformMatrix(inOrigin, inVertex);
	#else
		mat4 shaderTransformMatrix = mat4(1.0);
	#endif

	// compute vertex and pass to fragment shader
	computeVertex(vec4(inVertex, 1.0), inNormal, shaderTransformMatrix);
}
