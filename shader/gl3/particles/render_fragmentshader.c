#version 330

uniform sampler2D diffuseTextureUnit;
uniform vec4 effectColorMul;
uniform vec4 effectColorAdd;

in vec4 fragColor;
out vec4 outColor;

void main (void) {
	outColor = clamp(effectColorAdd + texture(diffuseTextureUnit, gl_PointCoord) * fragColor * effectColorMul, 0.0, 1.0);
}
