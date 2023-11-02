// based on
//	http://theorangeduck.com/page/pure-depth-ssao
//	https://hub.jmonkeyengine.org/t/depth-only-ssao/37749

#version 100

precision highp sampler2D;
precision highp float;

// uniforms
uniform sampler2D colorBufferTextureUnit;
uniform sampler2D depthBufferTextureUnit;
uniform sampler2D randomTextureUnit;
uniform float bufferTexturePixelWidth;
uniform float bufferTexturePixelHeight;
uniform vec3 sphere[16];

uniform float strength;
uniform float area;
uniform float falloff;
uniform float radius;
uniform int samples;

// passed from vertex shader
varying vec2 vsFragTextureUV;

vec3 normal_from_depth(float depth, vec2 texCoord) {

  vec2 offset1 = vec2(0.0, bufferTexturePixelHeight);
  vec2 offset2 = vec2(bufferTexturePixelWidth, 0.0);

  float depth1 = texture2D(depthBufferTextureUnit, texCoord + offset1).r;
  float depth2 = texture2D(depthBufferTextureUnit, texCoord + offset2).r;

  vec3 p1 = vec3(offset1, depth1 - depth);
  vec3 p2 = vec3(offset2, depth2 - depth);

  vec3 normal = cross(p1, p2);
  normal.z = -normal.z;

  return normalize(normal);
}

// main
void main(void) {
	float depth = texture2D(depthBufferTextureUnit, vsFragTextureUV).r;

	vec3 random = normalize(texture2D(randomTextureUnit, vsFragTextureUV * 64.0).rgb);

	vec3 position = vec3(vsFragTextureUV.x, vsFragTextureUV.y, depth);
	vec3 normal = normal_from_depth(depth, vsFragTextureUV);

	float radius_depth = radius / depth;
	float occlusion = 0.0;
	for(int i = 0; i < samples; i++) {

		vec3 ray = radius_depth * reflect(sphere[i], random);
		vec3 hemi_ray = position + sign(dot(ray,normal)) * ray;

		float occ_depth = texture2D(depthBufferTextureUnit, clamp(hemi_ray.xy, 0.0, 1.0)).r;
		float difference = depth - occ_depth;

		occlusion += step(falloff, difference) * (1.0 - smoothstep(falloff, area, difference));
	}

	float ao = 1.0 - strength * occlusion * (1.0 / float(samples));

	gl_FragColor.r = ao * 1.15;
	gl_FragColor.g = ao * 1.15;
	gl_FragColor.b = ao * 1.15;
	gl_FragColor.a = 1.0;
}
