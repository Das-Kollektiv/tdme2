#version 430 core

#define MAX_JOINTS	60

// structs

// layouts
layout(local_size_x=16, local_size_y=1, local_size_z=1) in;
layout(std430, binding=0) buffer InVertex { vec3 inVertex[]; };
layout(std430, binding=1) buffer InNormal { vec3 inNormal[]; };
layout(std430, binding=2) buffer InSkinningVertexJoints { int inSkinningVertexJoints[]; };
layout(std430, binding=3) buffer InSkinningVertexJointIdxs { ivec4 inSkinningVertexJointIdxs[]; };
layout(std430, binding=4) buffer InSkinningVertexJointWeights { vec4 inSkinningVertexJointWeights[]; };
layout(std430, binding=5) buffer OutVertex { vec3 outVertex[]; };
layout(std430, binding=6) buffer OutNormal { vec3 outNormal[]; };

// uniforms
uniform int skinningCount;
uniform mat4 skinningJointsTransformationsMatrices[MAX_JOINTS];

void main() {
	// TODO: tangents and bitangents
	uint offset = gl_GlobalInvocationID.x;
	if (offset < skinningCount) {
		vec4 skinnedVertex = vec4(0.0, 0.0, 0.0, 0.0);
		vec3 skinnedNormal = vec3(0.0, 0.0, 0.0);
		float totalWeights = 0.0;
		for (int i = 0; i < inSkinningVertexJoints[offset]; i++) {
			mat4 transformationsMatrix = skinningJointsTransformationsMatrices[inSkinningVertexJointIdxs[offset][i]];
			skinnedVertex+= transformationsMatrix * vec4(inVertex[offset], 1.0) * inSkinningVertexJointWeights[offset][i];
			skinnedNormal+= mat3(transformationsMatrix) * inNormal[offset] * inSkinningVertexJointWeights[offset][i];
			totalWeights+= inSkinningVertexJointWeights[offset][i];
		}
		if (totalWeights != 1.0) {
			float weightNormalized = totalWeights != 0.0?1.0 / totalWeights:0.0;
			skinnedVertex*= weightNormalized;
			skinnedNormal*= weightNormalized;
		}
		outVertex[offset] = skinnedVertex.xyz;
		outNormal[offset] = skinnedNormal;
	}
}
