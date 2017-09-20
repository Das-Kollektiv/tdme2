#version 100

precision highp float;

attribute vec3 inVertex;
attribute vec3 inNormal;
attribute vec2 inTextureUV;

uniform mat4 mvpMatrix;

void main(){
	gl_Position = mvpMatrix * vec4(inVertex, 1.0);
}
