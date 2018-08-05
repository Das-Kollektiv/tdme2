#version 330

#define GS_IN_ARRAY_AT(array, index) array[index]

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec2[] vsFragTextureUV;
in vec3[] vsNormal;
in vec3[] vsTangent;
in vec3[] vsBitangent;
in vec4[] vsEffectColorMul;
in vec4[] vsEffectColorAdd;
in mat4[] vsModelMatrix;

out vec2 gsFragTextureUV;
out vec3 gsPosition;
out vec3 gsNormal;
out vec3 gsTangent;
out vec3 gsBitangent;
out vec4 gsEffectColorMul;
out vec4 gsEffectColorAdd;

// uniforms
uniform mat4 projectionMatrix;
uniform mat4 cameraMatrix;
uniform mat3 textureMatrix;
uniform int normalTextureAvailable;
uniform int frame;

{$FUNCTIONS}

void main()
{
	vec3 verticesMin;
	vec3 verticesMax;
	vec3 verticesCenter;
	for (int i = 0; i < gl_in.length(); i++) {
		vec3 vertex = gl_in[i].gl_Position.xyz;
		if (i == 0) {
			verticesMin = vertex;
			verticesMax = vertex;
		} else {
			for (int j = 0; j < 3; j++) {
				if (vertex[j] < verticesMin[j]) verticesMin[j] = vertex[j];
				if (vertex[j] > verticesMax[j]) verticesMax[j] = vertex[j];
			}
		}
	}
	verticesCenter = verticesMin + ((verticesMax - verticesMin) / 2.0);

	float zAxisRotation = (frame + int(verticesCenter[0] * 8.0 * (verticesCenter[0] < 0.0?-1.0:1.0))) % 160;
	zAxisRotation = (((zAxisRotation < 160 / 2?zAxisRotation:160 - zAxisRotation) - (160 / 4)) * 1.0f / 8.0f);
	mat4 shaderTransformMatrix =
		createTranslationMatrix(vec3(verticesCenter[0], verticesMin[1], verticesCenter[2])) *
		createRotationMatrix(vec3(0.0, 0.0, 1.0), zAxisRotation) *
		createTranslationMatrix(vec3(verticesCenter[0], verticesMin[1], verticesCenter[2]) * -1.0);

	for (int i = 0; i < gl_in.length() / 3; i++) {
		computeVertex(gl_in[i * 3 + 0].gl_Position, i * 3 + 0, shaderTransformMatrix);
		EmitVertex();
		computeVertex(gl_in[i * 3 + 1].gl_Position, i * 3 + 1, shaderTransformMatrix);
		EmitVertex();
		computeVertex(gl_in[i * 3 + 2].gl_Position, i * 3 + 2, shaderTransformMatrix);
		EmitVertex();
		EndPrimitive();
	}
}
