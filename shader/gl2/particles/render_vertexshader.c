#version 120

// uniforms
uniform sampler2D diffuseTextureUnit;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform float pointSize;

// will be passed to fragment shader
varying vec4 fragColor;
  
void main(void) {
	// pass color to fragment shader
	fragColor = gl_Color;

	// compute gl position
	gl_Position = mvpMatrix * gl_Vertex;

	// point size
	gl_PointSize = pointSize * (1.0 / length((mvMatrix * gl_Vertex).xyz));
}
