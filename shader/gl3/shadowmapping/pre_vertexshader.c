#version 330

layout (location = 0) in vec3 inVertex;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureUV;

uniform mat4 mvpMatrix;

void main(){
	gl_Position = mvpMatrix * vec4(inVertex, 1.0);
}
