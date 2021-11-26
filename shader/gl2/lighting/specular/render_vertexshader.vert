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

#version 100

{$DEFINITIONS}

// standard layouts
attribute vec3 inVertex;
attribute vec3 inNormal;
attribute vec2 inTextureUV;
attribute vec3 inOrigin;

// uniforms
uniform mat4 projectionMatrix;
uniform mat4 cameraMatrix;
uniform mat4 normalMatrix;
uniform mat4 modelMatrix;
uniform mat3 textureMatrix;

uniform vec4 sceneColor;
uniform vec4 effectColorMul;
uniform float time;

#if defined(HAVE_WATER_SHADER)
	// uniforms
	uniform float waterHeight;
	uniform int waterWaves;
	uniform float waterAmplitude[4];
	uniform float waterWavelength[4];
	uniform float waterSpeed[4];
	uniform vec2 waterDirection[4];
#elif defined(HAVE_TERRAIN_SHADER)
	varying vec3 terrainVertex;
	varying vec3 terrainNormal;
	varying float terrainHeight;
	varying float terrainSlope;
#elif defined(HAVE_FOLIAGE)
	uniform float speed;
	uniform float amplitudeDefault;
	uniform float amplitudeMax;
#elif defined(HAVE_TREE)
	uniform float speed;
#endif

// will be passed to fragment shader
varying vec3 vsPosition;
varying vec3 vsNormal;
varying vec2 vsFragTextureUV;
varying vec4 vsFragColor;

{$FUNCTIONS}

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

#if !defined(HAVE_SPECULARMATERIAL_STRUCT)
#define HAVE_SPECULARMATERIAL_STRUCT
struct SpecularMaterial {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
	float reflection;
};
#endif

struct SpecularLight {
	int enabled;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
	vec3 spotDirection;
	float spotExponent;
	float spotCosCutoff;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	float radius;
};

#define FALSE		0
#define MAX_LIGHTS	8

uniform SpecularLight specularLights[MAX_LIGHTS];
uniform SpecularMaterial specularMaterial;

//
vec4 computeSpecularLight(in int i, in vec3 normal, in vec3 position, in vec3 eyeDirection, in SpecularMaterial specularMaterial) {
	vec3 lightDirection = specularLights[i].position.xyz - position.xyz;
	float lightDistance = length(lightDirection);
	lightDirection = normalize(lightDirection);
	vec3 reflectionDirection = normalize(reflect(-lightDirection, normal));

	// compute attenuation
	float lightAttenuation =
		1.0 /
		(
			specularLights[i].constantAttenuation +
			specularLights[i].linearAttenuation * lightDistance +
			specularLights[i].quadraticAttenuation * lightDistance * lightDistance
		);

	// see if point on surface is inside cone of illumination
	float lightSpotDot = dot(-lightDirection, normalize(specularLights[i].spotDirection));
	float lightSpotAttenuation = 0.0;
	if (lightSpotDot >= specularLights[i].spotCosCutoff) {
		lightSpotAttenuation = pow(lightSpotDot, specularLights[i].spotExponent);
	}

	// Combine the spotlight and distance attenuation.
	lightAttenuation *= lightSpotAttenuation;

	// add color components to fragment color
	return
		clamp(specularLights[i].ambient * specularMaterial.ambient, 0.0, 1.0) +
		clamp(specularLights[i].diffuse * specularMaterial.diffuse * max(dot(normal, lightDirection), 0.0) * lightAttenuation, 0.0, 1.0) +
		clamp(specularLights[i].specular * specularMaterial.specular * pow(max(dot(reflectionDirection, eyeDirection), 0.0), 0.3 * specularMaterial.shininess) * lightAttenuation, 0.0, 1.0);
}

//
vec4 computeSpecularLighting(in vec3 normal, in vec3 position, in vec3 eyeDirection, in SpecularMaterial specularMaterial) {
	vec4 fragColor = vec4(0.0, 0.0, 0.0, 0.0);
	// process each light
	for (int i = 0; i < MAX_LIGHTS; i++) {
		// skip on disabled specularLights
		if (specularLights[i].enabled == FALSE || (specularLights[i].radius > 0.0 && length(specularLights[i].position.xyz - position.xyz) > specularLights[i].radius)) continue;

		// compute light
		fragColor+= computeSpecularLight(i, normal, position, eyeDirection, specularMaterial);
	}
	//
	return fragColor;
}


void main(void) {
	mat4 _modelMatrix = modelMatrix;
	#if defined(HAVE_TREE)
		mat4 shaderTransformMatrix = createTreeTransformMatrix(
			inOrigin,
			inVertex * mat3(_modelMatrix),
			vec3(_modelMatrix[3][0], _modelMatrix[3][1], _modelMatrix[3][2])
		);
	#elif defined(HAVE_FOLIAGE)
		mat4 shaderTransformMatrix =
			createFoliageTransformMatrix(
				inOrigin,
				inVertex * mat3(_modelMatrix),
				vec3(_modelMatrix[3][0], _modelMatrix[3][1], _modelMatrix[3][2])
			);
	#else
		mat4 shaderTransformMatrix = mat4(1.0);
	#endif

	#if defined(HAVE_TERRAIN_SHADER)
		vec4 heightVector4 = _modelMatrix * vec4(inVertex, 1.0);
		vec3 heightVector3 = heightVector4.xyz / heightVector4.w;
		terrainVertex = heightVector3;
		terrainHeight = heightVector3.y;
		vec3 worldNormal = normalize(vec3(_modelMatrix * vec4(inNormal, 0.0)));
		terrainSlope = abs(180.0 / 3.14 * acos(clamp(dot(worldNormal, vec3(0.0, 1.0, 0.0)), -1.0, 1.0)));
		terrainNormal = normalize(vec3(normalMatrix * vec4(inNormal, 0.0)));
		vec3 normal = terrainNormal;
	#elif defined(HAVE_WATER_SHADER)
		// transformations matrices
		vec4 worldPosition4 = _modelMatrix * vec4(inVertex, 1.0);
		vec3 worldPosition = (worldPosition4.xyz / worldPosition4.w).xyz * 2.0;
		float height = waterHeight * waveHeight(worldPosition.x, worldPosition.z);
		_modelMatrix[1][1] = 1.0;
		shaderTransformMatrix =
			mat4(
				1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, height, 0.0, 1.0
			);
		vsNormal = waveNormal(worldPosition.x, worldPosition.z);
		vec3 normal = normalize(vec3(normalMatrix * shaderTransformMatrix * vec4(vsNormal, 0.0)));
	#else
		// compute the normal
		vec3 normal = normalize(vec3(normalMatrix * shaderTransformMatrix * vec4(inNormal, 0.0)));
	#endif

	// pass texture uv to fragment shader
	vsFragTextureUV = vec2(textureMatrix * vec3(inTextureUV, 1.0));

	//
	vsFragColor = vec4(0.0, 0.0, 0.0, 0.0);
	vsFragColor+= clamp(specularMaterial.emission, 0.0, 1.0);

	// compute gl position
	gl_Position = projectionMatrix * cameraMatrix * _modelMatrix * shaderTransformMatrix * vec4(inVertex, 1.0);

	// world position of vertex, needed in various calculations
	vec4 position4 = _modelMatrix * shaderTransformMatrix * vec4(inVertex, 1.0);
	vec3 position = position4.xyz / position4.w;

	// eye direction
	position4 = cameraMatrix * _modelMatrix * shaderTransformMatrix * vec4(inVertex, 1.0);
	vec3 eyeDirection = normalize(-position4.xyz / position4.w);

	// compute specular lights
	vsFragColor+= computeSpecularLighting(normal, vsPosition, eyeDirection, specularMaterial);

	// take effect colors into account
	vsFragColor*= effectColorMul;
	vsFragColor.a = specularMaterial.diffuse.a * effectColorMul.a;

	//
	vsPosition = position;
	vsNormal = normal;
}
