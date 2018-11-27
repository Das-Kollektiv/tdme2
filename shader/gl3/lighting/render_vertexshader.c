// Based on:
//	of some code of 3Dlabs Inc. Ltd.
//	and http://stackoverflow.com/questions/11365399/opengl-shader-a-spotlight-and-a-directional-light?answertab=active#tab-top
/************************************************************************
*                                                                       *                                                                       
*                                                                       *
*        Copyright (C) 2002-2004  3Dlabs Inc. Ltd.                      *
*                                                                       *
*                        All rights reserved.                           *
*                                                                       *
* Redistribution and use in source and binary forms, with or without    *
* modification, are permitted provided that the following conditions    *
* are met:                                                              *
*                                                                       *
*     Redistributions of source code must retain the above copyright    *
*     notice, this list of conditions and the following disclaimer.     *
*                                                                       *
*     Redistributions in binary form must reproduce the above           *
*     copyright notice, this list of conditions and the following       *
*     disclaimer in the documentation and/or other materials provided   *
*     with the distribution.                                            *
*                                                                       *
*     Neither the name of 3Dlabs Inc. Ltd. nor the names of its         *
*     contributors may be used to endorse or promote products derived   *
*     from this software without specific prior written permission.     *
*                                                                       *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS     *
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE        *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, *
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  *
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      *
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      *
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT    *
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN     *
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                           *
*                                                                       *
************************************************************************/

#version 330

// standard layouts
layout (location = 0) in vec3 inVertex;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureUV;

// normal mapping
layout (location = 4) in vec3 inTangent;
layout (location = 5) in vec3 inBitangent;

// indexed rendering
layout (location = 6) in mat4 inModelMatrix;
layout (location = 10) in vec4 inEffectColorMul;
layout (location = 11) in vec4 inEffectColorAdd;

// uniforms
uniform sampler2D displacementTextureUnit;
uniform int displacementTextureAvailable;
uniform mat3 textureMatrix;
uniform int normalTextureAvailable;

{$DEFINITIONS}

#if defined(HAVE_GEOMETRY_SHADER)
	// will be passed to geometry shader
	out mat4 vsModelMatrix;
	out vec2 vsFragTextureUV;
	out vec3 vsNormal;
	out vec3 vsTangent;
	out vec3 vsBitangent;
	out vec4 vsEffectColorMul;
	out vec4 vsEffectColorAdd;
#else
	uniform mat4 projectionMatrix;
	uniform mat4 cameraMatrix;

	// will be passed to fragment shader
	out vec2 gsFragTextureUV;
	out vec3 gsNormal;
	out vec3 gsTangent;
	out vec3 gsBitangent;
	out vec4 gsEffectColorMul;
	out vec4 gsEffectColorAdd;
	out vec3 gsPosition;

	#define vsModelMatrix inModelMatrix
	#define vsFragTextureUV inTextureUV
	#define vsNormal inNormal
	#define vsTangent inTangent
	#define vsBitangent inBitangent
	#define vsEffectColorMul inEffectColorMul
	#define vsEffectColorAdd inEffectColorAdd

	#define GS_IN_ARRAY_AT(array, index) array

	#if defined(HAVE_TERRAIN_SHADER)
		out vec4 terrainBlending;
	#endif
#endif

{$FUNCTIONS}

void main(void) {
	#if defined(HAVE_GEOMETRY_SHADER)
		// pass to geometry shader
		vsModelMatrix = inModelMatrix;
		vsFragTextureUV = inTextureUV;
		vsNormal = inNormal;
		if (normalTextureAvailable == 1) {
			vsTangent = inTangent;
			vsBitangent = inBitangent;
		}
		vsEffectColorMul = inEffectColorMul;
		vsEffectColorAdd = inEffectColorAdd;
		// compute gl position
		if (displacementTextureAvailable == 1) {
			vec3 displacementVector = texture(displacementTextureUnit, vsFragTextureUV).rgb * 2.0 - 1.0;
			/*
			float displacementLength = (displacementVector.x + displacementVector.y + displacementVector.z) / 3.0;
			skinnedInVertex-=
				vec4(normalize(skinnedInNormal) * displacementLength, 0.0);
			*/
		}
		// gl position
		gl_Position = vec4(inVertex, 1.0);
	#else
		//
		#if defined(HAVE_TERRAIN_SHADER)
			#define TERRAIN_LEVEL_0	0.0
			#define TERRAIN_LEVEL_1	10.0

			vec4 heightVector4 = inModelMatrix * vec4(inVertex, 1.0);
			vec3 heightVector3 = heightVector4.xyz / heightVector4.w;
			float height = heightVector3.y;

			mat4 normalMatrix = mat4(transpose(inverse(mat3(inModelMatrix))));
			vec4 normalVector4 = normalMatrix * vec4(inNormal, 0.0);
			vec3 normalVector3 = normalize(normalVector4.xyz);
			float slope = abs(180.0 / 3.14 * acos(clamp(dot(normalVector3, vec3(0.0, 1.0, 0.0)), -1.0, 1.0)));

			terrainBlending[0] = 0.0; // gras
			terrainBlending[1] = 0.0; // dirt
			terrainBlending[2] = 0.0; // stone
			terrainBlending[3] = 0.0; // snow

			// height
			if (height >= TERRAIN_LEVEL_1) {
				float blendFactorHeight = clamp(height - TERRAIN_LEVEL_1, 0.0, 1.0);
				// 10+ meter
				if (slope > 45.0) {
					terrainBlending[2] = 1.0 * blendFactorHeight; // stone
				} else {
					terrainBlending[3] = 1.0 * blendFactorHeight; // snow
				}
			} else
			if (height >= TERRAIN_LEVEL_0) {
				float blendFactorHeight = clamp(height - TERRAIN_LEVEL_0, 0.0, 1.0);
				// 0..10 meter
				if (slope > 45.0) {
					terrainBlending[2] = 1.0 * blendFactorHeight; // stone
				} else
				if (slope > 26.0) {
					terrainBlending[1] = 1.0 * blendFactorHeight; // dirt
				} else {
					terrainBlending[0] = 1.0 * blendFactorHeight; // gras
				}
			} else {
				float blendFactorHeight = clamp(-height, 0.0, 1.0);
				// 0- meter
				terrainBlending[1] = 1.0 * blendFactorHeight; // dirt
			}
		#endif

		// compute vertex and pass to fragment shader
		computeVertex(vec4(inVertex, 1.0), -1, mat4(1.0));
	#endif
}
