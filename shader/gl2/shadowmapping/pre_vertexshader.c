#version 120

uniform mat4 mvpMatrix;

void main(){
	gl_Position = mvpMatrix * gl_Vertex;
}
