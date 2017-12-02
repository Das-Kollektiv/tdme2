#version 330

precision highp float;
precision highp int;
precision highp sampler2D;

// layout
layout (location = 0) in vec3 inVertex;
layout (location = 3) in vec4 inColor;

// uniforms
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform float pointSize;

// will be passed to fragment shader
out vec4 fragColor;
  
void main(void) {
	//
	fragColor = inColor;

	// compute gl position
	gl_Position = mvpMatrix * vec4(inVertex, 1.0);

	// point size
	gl_PointSize = pointSize * (1.0 / length((mvMatrix * vec4(inVertex, 1.0)).xyz));
}
