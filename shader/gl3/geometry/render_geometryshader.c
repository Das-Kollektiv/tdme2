#version 330

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
uniform int normalTextureAvailable;
uniform int frame;
uniform int applyFoliageAnimation;

// global variables
mat4 shaderTransformMatrix;

//
void computeVertex(int vertexIdx) {
	// Emit a primitive only if the sign of the dot product is positive
	mat4 mvMatrix = cameraMatrix * vsModelMatrix[vertexIdx] * shaderTransformMatrix;
	mat4 mvpMatrix = projectionMatrix * cameraMatrix * vsModelMatrix[vertexIdx] * shaderTransformMatrix;
	mat4 normalMatrix = mat4(transpose(inverse(mat3(cameraMatrix * vsModelMatrix[vertexIdx] * shaderTransformMatrix))));

	gsFragTextureUV = vsFragTextureUV[vertexIdx];

	// compute the normal
	gsNormal = normalize(vec3(normalMatrix * vec4(vsNormal[vertexIdx], 0.0)));

	// normal texture
	if (normalTextureAvailable == 1) {
		gsTangent = normalize(vec3(normalMatrix * vec4(vsTangent[vertexIdx], 0.0)));
		gsBitangent = normalize(vec3(normalMatrix * vec4(vsBitangent[vertexIdx], 0.0)));
	} else {
		gsTangent = vec3(0.0, 0.0, 0.0);
		gsBitangent = vec3(0.0, 0.0, 0.0);
	}

	gsEffectColorMul = vsEffectColorMul[vertexIdx];
	gsEffectColorAdd = vsEffectColorAdd[vertexIdx];

	vec4 gsPosition4 = mvMatrix * gl_in[vertexIdx].gl_Position;
	gl_Position = mvpMatrix * gl_in[vertexIdx].gl_Position;
	gsPosition = gsPosition4.xyz / gsPosition4.w;
}

mat4 createRotationMatrix(vec3 axis, float angle) {
    float c = cos(angle * 0.017453294);
    float s = sin(angle * 0.017453294);
    float c1 = 1.0 - c;
    float m0 = 1.0;
    float m1 = 0.0;
    float m2 = 0.0;
    float m3 = 0.0;
    float m4 = 0.0;
    float m5 = 1.0;
    float m6 = 0.0;
    float m7 = 0.0;
    float m8 = 0.0;
    float m9 = 0.0;
    float m10 = 1.0;
    float m11 = 0.0;
    float m12 = 0.0;
    float m13 = 0.0;
    float m14 = 0.0;
    float m15 = 1.0;
    float r0 = axis[0] * axis[0] * c1 + c;
    float r1 = axis[0] * axis[1] * c1 + axis[2] * s;
    float r2 = axis[0] * axis[2] * c1 - axis[1] * s;
    float r4 = axis[0] * axis[1] * c1 - axis[2] * s;
    float r5 = axis[1] * axis[1] * c1 + c;
    float r6 = axis[1] * axis[2] * c1 + axis[0] * s;
    float r8 = axis[0] * axis[2] * c1 + axis[1] * s;
    float r9 = axis[1] * axis[2] * c1 - axis[0] * s;
    float r10= axis[2] * axis[2] * c1 + c;
    return mat4(
		r0 * m0 + r4 * m1 + r8 * m2,
		r1 * m0 + r5 * m1 + r9 * m2,
		r2 * m0 + r6 * m1 + r10* m2,
		0.0,
		r0 * m4 + r4 * m5 + r8 * m6,
		r1 * m4 + r5 * m5 + r9 * m6,
		r2 * m4 + r6 * m5 + r10* m6,
		0.0,
		r0 * m8 + r4 * m9 + r8 * m10,
		r1 * m8 + r5 * m9 + r9 * m10,
		r2 * m8 + r6 * m9 + r10* m10,
		0.0,
		r0 * m12+ r4 * m13+ r8 * m14,
		r1 * m12+ r5 * m13+ r9 * m14,
		r2 * m12+ r6 * m13+ r10* m14,
		1.0
	);
}

mat4 createTranslationMatrix(vec3 translation) {
	return mat4(
		1.0,
		0.0,
		0.0,
		0.0,
		0.0,
		1.0,
		0.0,
		0.0,
		0.0,
		0.0,
		1.0,
		0.0,
		translation[0],
		translation[1],
		translation[2],
		1.0
	);
}

void main()
{
	if (applyFoliageAnimation == 1) {
		vec3 verticesMin;
		vec3 verticesMax;
		vec3 verticesCenter;
		for (int i = 0; i < gl_in.length(); i++) {
			vec3 vertex = (vsModelMatrix[i] * gl_in[i].gl_Position).xyz;
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
		shaderTransformMatrix =
			createTranslationMatrix(vec3(verticesCenter[0], verticesMin[1], verticesCenter[2])) *
			createRotationMatrix(vec3(0.0, 0.0, 1.0), zAxisRotation) *
			createTranslationMatrix(vec3(verticesCenter[0], verticesMin[1], verticesCenter[2]) * -1.0);
	} else {
		shaderTransformMatrix = mat4(1.0);
	}

	for (int i = 0; i < gl_in.length() / 3; i++) {
		computeVertex(i * 3 + 0);
		EmitVertex();
		computeVertex(i * 3 + 1);
		EmitVertex();
		computeVertex(i * 3 + 2);
		EmitVertex();
		EndPrimitive();
	}
}
