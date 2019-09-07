#version 330

precision highp float;
precision highp int;

// layout
layout (location = 0) in vec3 inVertex;
layout (location = 3) in vec4 inColor;

// uniforms
uniform mat4 mvpMatrix;

// will be passed to fragment shader
out vec4 fragColor;

#if defined(HAVE_DEPTH_FOG)
	out float fragDepth;
#endif

void main(void) {
	//
	fragColor = inColor;

	// compute gl position
	gl_Position = mvpMatrix * vec4(inVertex, 1.0);

	//
	#if defined(HAVE_DEPTH_FOG)
		fragDepth = gl_Position.z;
	#endif
}
