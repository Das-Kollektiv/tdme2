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

#define FALSE		0
#define MAX_LIGHTS	8

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
};

struct Light {
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
};

uniform Material material;
uniform Light lights[MAX_LIGHTS];

uniform vec4 sceneColor;

uniform sampler2D specularTextureUnit;
uniform int specularTextureAvailable;

uniform sampler2D normalTextureUnit;
uniform int normalTextureAvailable;

// material shininess
float materialShininess;

// passed from geometry shader
in vec2 gsFragTextureUV;
in vec3 gsPosition;
in vec3 gsNormal;
in vec3 gsTangent;
in vec3 gsBitangent;
in vec4 gsEffectColorMul;
in vec4 gsEffectColorAdd;

// out
out vec4 outColor;

vec4 fragColor;

{$DEFINITIONS}

#if defined(HAVE_TERRAIN_SHADER)
	in float slope;
	in float height;
	uniform sampler2D grasTextureUnit;
	uniform sampler2D dirtTextureUnit;
	uniform sampler2D stoneTextureUnit;
	uniform sampler2D snowTextureUnit;
#else
	uniform sampler2D diffuseTextureUnit;
	uniform int diffuseTextureAvailable;
	uniform int diffuseTextureMaskedTransparency;
	uniform float diffuseTextureMaskedTransparencyThreshold;
#endif

void computeLight(in int i, in vec3 normal, in vec3 position) {
	vec3 lightDirection = lights[i].position.xyz - position.xyz;
	float lightDistance = length(lightDirection);
	lightDirection = normalize(lightDirection);
	vec3 eyeDirection = normalize(-position);
	vec3 reflectionDirection = normalize(reflect(-lightDirection, normal));

	// compute attenuation
	float lightAttenuation =
		1.0 /
		(
			lights[i].constantAttenuation +
			lights[i].linearAttenuation * lightDistance +
			lights[i].quadraticAttenuation * lightDistance * lightDistance
		);
 
	// see if point on surface is inside cone of illumination
	float lightSpotDot = dot(-lightDirection, normalize(lights[i].spotDirection));
	float lightSpotAttenuation = 0.0;
	if (lightSpotDot >= lights[i].spotCosCutoff) {
		lightSpotAttenuation = pow(lightSpotDot, lights[i].spotExponent);
	}

	// Combine the spotlight and distance attenuation.
	lightAttenuation *= lightSpotAttenuation;

	// add color components to fragment color
	fragColor+=
		clamp(lights[i].ambient * material.ambient, 0.0, 1.0) +
		clamp(lights[i].diffuse * material.diffuse * max(dot(normal, lightDirection), 0.0) * lightAttenuation, 0.0, 1.0) +
		clamp(lights[i].specular * material.specular * pow(max(dot(reflectionDirection, eyeDirection), 0.0), 0.3 * materialShininess) * lightAttenuation, 0.0, 1.0);
}

void computeLights(in vec3 normal, in vec3 position) {
	// process each light
	for (int i = 0; i < MAX_LIGHTS; i++) {
		// skip on disabled lights
		if (lights[i].enabled == FALSE) continue;

		// compute light
		computeLight(i, normal, position);
	}
}

void main (void) {
	// retrieve diffuse texture color value
	#if defined(HAVE_TERRAIN_SHADER)
		// no op
	#else
		vec4 diffuseTextureColor;
		if (diffuseTextureAvailable == 1) {
			// fetch from texture
			diffuseTextureColor = texture(diffuseTextureUnit, gsFragTextureUV);
			// check if to handle diffuse texture masked transparency
			if (diffuseTextureMaskedTransparency == 1) {
				// discard if beeing transparent
				if (diffuseTextureColor.a < diffuseTextureMaskedTransparencyThreshold) discard;
				// set to opqaue
				diffuseTextureColor.a = 1.0;
			}
		}
	#endif

	//
	fragColor = vec4(0.0, 0.0, 0.0, 0.0);
	fragColor+= clamp(sceneColor, 0.0, 1.0);
	fragColor+= clamp(material.emission, 0.0, 1.0);

	vec3 normal = gsNormal;

	// specular
	materialShininess = material.shininess;
	if (specularTextureAvailable == 1) {
		vec3 specularTextureValue = texture(specularTextureUnit, gsFragTextureUV).rgb;
		materialShininess =
			((0.33 * specularTextureValue.r) +
			(0.33 * specularTextureValue.g) +
			(0.33 * specularTextureValue.b)) * 255.0;
	}

	// compute normal
	if (normalTextureAvailable == 1) {
		vec3 normalVector = normalize(texture(normalTextureUnit, gsFragTextureUV).rgb * 2.0 - 1.0);
		normal = vec3(0.0, 0.0, 0.0);
		normal+= gsTangent * normalVector.x;
		normal+= gsBitangent * normalVector.y;
		normal+= gsNormal * normalVector.z;
	}

 	// compute lights
	computeLights(normal, gsPosition);

	// take effect colors into account
	fragColor = fragColor * gsEffectColorMul;
	fragColor.a = material.diffuse.a * gsEffectColorMul.a;

	//
	#if defined(HAVE_TERRAIN_SHADER)
		#define TERRAIN_LEVEL_0				2.0
		#define TERRAIN_LEVEL_1				12.0
		#define TERRAIN_HEIGHT_BLEND		4.0

		vec4 terrainBlending; // gras, dirt, stone, snow

		// height
		if (height > TERRAIN_LEVEL_1) {
			float blendFactorHeight = clamp((height - TERRAIN_LEVEL_1) / TERRAIN_HEIGHT_BLEND, 0.0, 1.0);
			// 10+ meter
			//if (slope > 45.0) {
			//	terrainBlending[2] = blendFactorHeight; // stone
			//} else {
				terrainBlending[3] = blendFactorHeight; // snow
			//}
		}
		if (height >= TERRAIN_LEVEL_0 && height < TERRAIN_LEVEL_1 + TERRAIN_HEIGHT_BLEND) {
			float blendFactorHeight = 1.0;
			if (height > TERRAIN_LEVEL_1) {
				blendFactorHeight = 1.0 - clamp((height - TERRAIN_LEVEL_1) / TERRAIN_HEIGHT_BLEND, 0.0, 1.0);
			} else
			if (height < TERRAIN_LEVEL_0 + TERRAIN_HEIGHT_BLEND) {
				blendFactorHeight = clamp((height - TERRAIN_LEVEL_0) / TERRAIN_HEIGHT_BLEND, 0.0, 1.0);
			}

			// 0..10 meter
			//if (slope > 45.0) {
			//	terrainBlending[2] = 1.0 * blendFactorHeight; // stone
			//} else
			//if (slope > 26.0) {
			//	terrainBlending[1] = 1.0 * blendFactorHeight; // dirt
			//} else {
				terrainBlending[0] = 1.0 * blendFactorHeight; // gras
			//}
		}
		if (height < TERRAIN_LEVEL_0 + TERRAIN_HEIGHT_BLEND) {
			float blendFactorHeight = 1.0;
			if (height > TERRAIN_LEVEL_0) {
				blendFactorHeight = 1.0 - clamp((height - TERRAIN_LEVEL_0) / TERRAIN_HEIGHT_BLEND, 0.0, 1.0);
			}
			// 0- meter
			terrainBlending[1] = 1.0 * blendFactorHeight; // dirt
		}

		//
		outColor = gsEffectColorAdd;
		if (terrainBlending[0] > 0.001) outColor+= texture(grasTextureUnit, gsFragTextureUV) * terrainBlending[0];
		if (terrainBlending[1] > 0.001) outColor+= texture(dirtTextureUnit, gsFragTextureUV) * terrainBlending[1];
		if (terrainBlending[2] > 0.001) outColor+= texture(stoneTextureUnit, gsFragTextureUV) * terrainBlending[2];
		if (terrainBlending[3] > 0.001) outColor+= texture(snowTextureUnit, gsFragTextureUV) * terrainBlending[3];
		outColor*= fragColor;
		outColor = clamp(outColor, 0.0, 1.0);
	#else
		if (diffuseTextureAvailable == 1) {
			outColor = clamp((gsEffectColorAdd + diffuseTextureColor) * fragColor, 0.0, 1.0);
		} else {
			outColor = clamp(gsEffectColorAdd + fragColor, 0.0, 1.0);
		}
	#endif
}
