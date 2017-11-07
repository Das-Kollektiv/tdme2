#version 100

precision highp float;

attribute vec3 inVertex;
attribute vec3 inNormal;
attribute vec2 inTextureUV;

uniform mat4 mvpMatrix;

// will be passed to fragment shader
varying vec2 vsFragTextureUV;

void main(){
	// pass texture uv to fragment shader
	vsFragTextureUV = inTextureUV;

	// position
	gl_Position = mvpMatrix * vec4(inVertex, 1.0);
}
