#version 330

// based on http://fabiensanglard.net/shadowmapping/index.php, modified by me

// standard layouts
layout (location = 0) in vec3 inVertex;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureUV;

// indexed rendering
layout (location = 6) in mat4 inModelMatrix;

// uniforms
// uniforms
uniform mat4 projectionMatrix;
uniform mat4 cameraMatrix;
uniform mat4 depthBiasMVPMatrix;
uniform vec3 lightPosition;
uniform vec3 lightDirection;
uniform mat3 textureMatrix;

{$DEFINITIONS}

#if defined(HAVE_GEOMETRY_SHADER) == false
	// will be passed to fragment shader
	out vec2 gsFragTextureUV;
	out vec4 gsShadowCoord;
	out float gsShadowIntensity;
	out vec3 gsPosition;

	#define vsNormal inNormal
	#define vsFragTextureUV inTextureUV
	#define vsModelMatrix inModelMatrix

	#define GS_IN_ARRAY_AT(array, index) array

#else
	// will be passed to geometry shader
	out vec2 vsFragTextureUV;
	out vec3 vsNormal;
	out mat4 vsModelMatrix;
#endif

{$FUNCTIONS}

void main() {
	#if defined(HAVE_GEOMETRY_SHADER)
		// pass to geometry shader
		vsFragTextureUV = inTextureUV;
		vsNormal = inNormal;
		vsModelMatrix = inModelMatrix;
		gl_Position = vec4(inVertex, 1.0);
	#else
		// compute vertex and pass to fragment shader
		computeVertex(vec4(inVertex, 1.0), -1, mat4(1.0));
	#endif
}
