#version 110

// uniforms
uniform sampler2D colorBufferTextureUnit;
uniform sampler2D depthBufferTextureUnit;
uniform float bufferTexturePixelWidth;
uniform float bufferTexturePixelHeight;

// passed from vertex shader
varying vec2 vsFragTextureUV;

// main
void main (void) {
	gl_FragColor = texture2D(colorBufferTextureUnit, vsFragTextureUV);
	gl_FragDepth = texture2D(depthBufferTextureUnit, vsFragTextureUV).r;
}
