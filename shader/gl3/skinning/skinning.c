#version 430 core

// layouts
layout(local_size_x=16,local_size_y=16) in;
layout(std430,binding=0) buffer InVertex { float inVertexFloatArray[]; };
layout(std430,binding=1) buffer InNormal { float inNormalFloatArray[]; };
layout(std430,binding=2) buffer InSkinningVertexJoints { int inSkinningVertexJoints[]; };
layout(std430,binding=3) buffer InSkinningVertexJointIdxs { int inSkinningVertexJointIdxs[]; };
layout(std430,binding=4) buffer InSkinningVertexJointWeights { float inSkinningVertexJointWeights[]; };
layout(std430,binding=5) buffer OutVertex { float outVertexFloatArray[]; };
layout(std430,binding=6) buffer OutNormal { float outNormalFloatArray[]; };
layout(std430,binding=7) buffer InSkinningJointsTransformationMatrices{ mat4 inSkinningJointsTransformationsMatrices[]; };

// uniforms
uniform int vertexCount;
uniform int matrixCount;
uniform int instanceCount;

void main() {
	// TODO: tangents and bitangents
	int vertexOffset = int(gl_GlobalInvocationID.x);
	int instance = int(gl_GlobalInvocationID.y);
	if (instance < instanceCount && vertexOffset < vertexCount) {
		vec3 skinnedVertex = vec3(0.0, 0.0, 0.0);
		vec3 skinnedNormal = vec3(0.0, 0.0, 0.0);
		float totalWeights = 0.0;
		vec3 inVertex = vec3(inVertexFloatArray[vertexOffset * 3 + 0], inVertexFloatArray[vertexOffset * 3 + 1], inVertexFloatArray[vertexOffset * 3 + 2]);
		vec3 inNormal = vec3(inNormalFloatArray[vertexOffset * 3 + 0], inNormalFloatArray[vertexOffset * 3 + 1], inNormalFloatArray[vertexOffset * 3 + 2]);
		for (int i = 0; i < inSkinningVertexJoints[vertexOffset]; i++) {
			mat4 transformationsMatrix = inSkinningJointsTransformationsMatrices[instance * matrixCount + inSkinningVertexJointIdxs[vertexOffset * 4 + i]];
			skinnedVertex+= (transformationsMatrix * vec4(inVertex, 1.0)).xyz * inSkinningVertexJointWeights[vertexOffset * 4 + i];
			skinnedNormal+= (mat3(transformationsMatrix) * inNormal) * inSkinningVertexJointWeights[vertexOffset * 4 + i];
			totalWeights+= inSkinningVertexJointWeights[vertexOffset * 4 + i];
		}
		if (totalWeights != 1.0) {
			float weightNormalized = totalWeights != 0.0?1.0 / totalWeights:0.0;
			skinnedVertex*= weightNormalized;
			skinnedNormal*= weightNormalized;
		}
		outVertexFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 0] = skinnedVertex.x;
		outVertexFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 1] = skinnedVertex.y;
		outVertexFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 2] = skinnedVertex.z;
		outNormalFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 0] = skinnedNormal.x;
		outNormalFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 1] = skinnedNormal.y;
		outNormalFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 2] = skinnedNormal.z;
	}
}
