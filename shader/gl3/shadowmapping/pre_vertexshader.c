#version 330

layout (location = 0) in vec3 inVertex;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureUV;

uniform mat4 mvpMatrix;

// will be passed to fragment shader
out vec2 vsFragTextureUV;

void main(){
	// pass texture uv to fragment shader
	vsFragTextureUV = inTextureUV;

	// position
	gl_Position = mvpMatrix * vec4(inVertex, 1.0);
}
