#version 100

// layouts
attribute vec3 inVertex;
attribute float inSpriteIndex;
attribute vec4 inColor;

// uniforms
uniform mat4 mvpMatrix;
uniform float pointSize;
uniform int viewPortWidth;
uniform int viewPortHeight;
uniform float projectionMatrixXx;
uniform float projectionMatrixYy;


// will be passed to fragment shader
varying vec4 vsFragColor;
varying float vsSpriteIndex;

void main(void) {
	//
	vsFragColor = inColor;
	vsSpriteIndex = inSpriteIndex;

	// compute gl position
	gl_Position = mvpMatrix * vec4(inVertex, 1.0);

	// point size
	gl_PointSize = (viewPortWidth > viewPortHeight?viewPortWidth * projectionMatrixXx * pointSize:viewPortHeight * projectionMatrixYy * pointSize) / gl_Position.w;
}
