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
layout (location = 6) in vec3 inBitangent;

// indexed rendering
layout (location = 6) in mat4 inMvMatrix;
layout (location = 10) in vec4 inEffectColorMul;
layout (location = 11) in vec4 inEffectColorAdd;

// uniforms
uniform mat4 projectionMatrix;
uniform sampler2D displacementTextureUnit;
uniform int displacementTextureAvailable;
uniform int normalTextureAvailable;

// will be passed to fragment shader
out vec2 vsFragTextureUV;
out vec3 vsPosition;
out vec3 vsNormal;
out vec3 vsTangent;
out vec3 vsBitangent;
out vec4 vsEffectColorMul;
out vec4 vsEffectColorAdd;

void main(void) {
	// pass to fragment shader
	vsFragTextureUV = inTextureUV;
	vsEffectColorMul = inEffectColorMul;
	vsEffectColorAdd = inEffectColorAdd;

	// compute gl position
	if (displacementTextureAvailable == 1) {
		vec3 displacementVector = texture(displacementTextureUnit, inTextureUV).rgb * 2.0 - 1.0;
		/*
		float displacementLength = (displacementVector.x + displacementVector.y + displacementVector.z) / 3.0;
		skinnedInVertex-=
			vec4(normalize(skinnedInNormal) * displacementLength, 0.0);
		*/
	}

	// vertices, normals
	gl_Position = (inMvMatrix * projectionMatrix) * vec4(inVertex, 1.0);

	// eye coordinate position of vertex, needed in various calculations
	vec4 vsPosition4 = inMvMatrix * vec4(inVertex, 1.0);
	vsPosition = vsPosition4.xyz / vsPosition4.w;

	// normal matrix
	mat4 normalMatrix = mat4(transpose(inverse(mat3(inMvMatrix))));

	// compute the normal
	vsNormal = normalize(vec3(normalMatrix * vec4(inNormal, 0.0)));

	// normal texture
	if (normalTextureAvailable == 1) {
		vsTangent = normalize(vec3(normalMatrix * vec4(inTangent, 0.0)));
		vsBitangent = normalize(vec3(normalMatrix * vec4(inBitangent, 0.0)));
	}
}
