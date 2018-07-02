#version 430 core

// layouts
layout(local_size_x=16) in;
layout(std430,binding=0) buffer InVertex { float inVertexFloatArray[]; };
layout(std430,binding=1) buffer InNormal { float inNormalFloatArray[]; };
layout(std430,binding=2) buffer InSkinningVertexJoints { int inSkinningVertexJoints[]; };
layout(std430,binding=3) buffer InSkinningVertexJointIdxs { ivec4 inSkinningVertexJointIdxs[]; };
layout(std430,binding=4) buffer InSkinningVertexJointWeights { vec4 inSkinningVertexJointWeights[]; };
layout(std430,binding=5) buffer OutVertex { float outVertexFloatArray[]; };
layout(std430,binding=6) buffer OutNormal { float outNormalFloatArray[]; };
layout(std430,binding=7) buffer InSkinningJointsTransformationMatrices{ mat4 inSkinningJointsTransformationsMatrices[]; };

// uniforms
uniform int skinningCount;

void main() {
	// TODO: tangents and bitangents
	int offset = int(gl_GlobalInvocationID.x);
	if (offset < skinningCount) {
		vec3 skinnedVertex = vec3(0.0, 0.0, 0.0);
		vec3 skinnedNormal = vec3(0.0, 0.0, 0.0);
		float totalWeights = 0.0;
		vec3 inVertex = vec3(inVertexFloatArray[offset * 3 + 0], inVertexFloatArray[offset * 3 + 1], inVertexFloatArray[offset * 3 + 2]);
		vec3 inNormal = vec3(inNormalFloatArray[offset * 3 + 0], inNormalFloatArray[offset * 3 + 1], inNormalFloatArray[offset * 3 + 2]);
		for (int i = 0; i < inSkinningVertexJoints[offset]; i++) {
			mat4 transformationsMatrix = inSkinningJointsTransformationsMatrices[inSkinningVertexJointIdxs[offset][i]];
			skinnedVertex+= (transformationsMatrix * vec4(inVertex, 1.0)).xyz * inSkinningVertexJointWeights[offset][i];
			skinnedNormal+= (mat3(transformationsMatrix) * inNormal) * inSkinningVertexJointWeights[offset][i];
			totalWeights+= inSkinningVertexJointWeights[offset][i];
		}
		if (totalWeights != 1.0) {
			float weightNormalized = totalWeights != 0.0?1.0 / totalWeights:0.0;
			skinnedVertex*= weightNormalized;
			skinnedNormal*= weightNormalized;
		}
		outVertexFloatArray[offset * 3 + 0] = skinnedVertex.x;
		outVertexFloatArray[offset * 3 + 1] = skinnedVertex.y;
		outVertexFloatArray[offset * 3 + 2] = skinnedVertex.z;
		outNormalFloatArray[offset * 3 + 0] = skinnedNormal.x;
		outNormalFloatArray[offset * 3 + 1] = skinnedNormal.y;
		outNormalFloatArray[offset * 3 + 2] = skinnedNormal.z;
	}
}
