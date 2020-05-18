#version 330

precision highp float;
precision highp int;

// layout
layout (location = 0) in vec3 inVertex;
layout (location = 1) in int inSpriteIndex;
layout (location = 3) in vec4 inColor;

// uniforms
uniform mat4 mvpMatrix;
uniform float pointSize;
uniform int viewPortWidth;
uniform int viewPortHeight;
uniform float projectionMatrixXx;
uniform float projectionMatrixYy;

// will be passed to fragment shader
flat out int vsSpriteIndex;
out vec4 vsFragColor;

#if defined(HAVE_DEPTH_FOG)
	out float fragDepth;
#endif

void main(void) {
	//
	vsFragColor = inColor;
	vsSpriteIndex = inSpriteIndex;

	// compute gl position
	gl_Position = mvpMatrix * vec4(inVertex, 1.0);

	// point size
	gl_PointSize = (viewPortWidth > viewPortHeight?viewPortWidth * projectionMatrixXx * pointSize:viewPortHeight * projectionMatrixYy * pointSize) / gl_Position.w;

	//
	#if defined(HAVE_DEPTH_FOG)
		fragDepth = gl_Position.z;
	#endif
}
