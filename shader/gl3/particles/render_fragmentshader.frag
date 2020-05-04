#version 330

uniform sampler2D diffuseTextureUnit;
uniform vec4 effectColorMul;
uniform vec4 effectColorAdd;
uniform int spritesHorizontal;
uniform int spritesVertical;
flat in int vsSpriteIndex;
in vec4 vsFragColor;
out vec4 outColor;

#if defined(HAVE_DEPTH_FOG)
	#define FOG_DISTANCE_NEAR			100.0
	#define FOG_DISTANCE_MAX			250.0
	#define FOG_RED						(255.0 / 255.0)
	#define FOG_GREEN					(255.0 / 255.0)
	#define FOG_BLUE					(255.0 / 255.0)
	in float fragDepth;
#endif

void main(void) {
	vec2 spriteCoord = (gl_PointCoord / vec2(spritesHorizontal, spritesVertical)) + vec2((1.0 / spritesHorizontal) * int(vsSpriteIndex % 4), 1.0 - ((1.0 / spritesHorizontal) * int(vsSpriteIndex / 4)));
	outColor = clamp(effectColorAdd + texture(diffuseTextureUnit, spriteCoord) * vsFragColor * effectColorMul, 0.0, 1.0);
	#if defined(HAVE_DEPTH_FOG)
		if (fragDepth > FOG_DISTANCE_NEAR) {
			float fogStrength = (clamp(fragDepth, FOG_DISTANCE_NEAR, FOG_DISTANCE_MAX) - FOG_DISTANCE_NEAR) * 1.0 / (FOG_DISTANCE_MAX - FOG_DISTANCE_NEAR);
			outColor = vec4(
				(outColor.rgb * (1.0 - fogStrength)) +
				vec3(FOG_RED, FOG_GREEN, FOG_BLUE) * fogStrength,
				outColor.a
			);
		}
	#endif
}
