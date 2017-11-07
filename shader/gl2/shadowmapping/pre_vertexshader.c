#version 120

uniform mat4 mvpMatrix;

// will be passed to fragment shader
varying vec2 vsFragTextureUV;

void main(){
	// pass texture uv to fragment shader
	vsFragTextureUV = vec2(gl_MultiTexCoord0);

	// position
	gl_Position = mvpMatrix * gl_Vertex;
}
