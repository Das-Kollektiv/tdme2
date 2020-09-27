#version 330

uniform sampler2D diffuseTextureUnits[48];

flat in int vsTextureIndex;
flat in int vsSpriteIndex;
flat in vec4 vsColor;
flat in ivec2 vsSpriteSheetDimension;
flat in vec4 vsEffectColorMul;
flat in vec4 vsEffectColorAdd;

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
	vec2 spriteCoord = gl_PointCoord / vsSpriteSheetDimension + vec2((1.0 / float(vsSpriteSheetDimension.x)) * int(vsSpriteIndex % 4), 1.0 - ((1.0 / float(vsSpriteSheetDimension.y)) * int(vsSpriteIndex / 4)));
	outColor = clamp(vsEffectColorAdd + texture(diffuseTextureUnits[vsTextureIndex], spriteCoord) * vsColor * vsEffectColorMul, 0.0, 1.0);
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
