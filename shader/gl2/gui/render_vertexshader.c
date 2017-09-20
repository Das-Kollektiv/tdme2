#version 120

// will be passed to fragment shader
varying vec4 vsFragColor;
varying vec2 vsFragTextureUV;

// main
void main(void) {
	// pass color to fragment shader
	vsFragColor = gl_Color;
	vsFragTextureUV = vec2(gl_MultiTexCoord0);

	// compute gl position
	gl_Position = gl_Vertex.xyzw;
}
