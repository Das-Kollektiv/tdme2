static float4 mat4MULvec4(float16 mat4, float4 vec4) {
	float4 result = float4(0.0, 0.0, 0.0, 0.0);
	result[0] = vec4[0] * mat4[0] + vec4[1] * mat4[4] + vec4[2] * mat4[8] + vec4[3] * mat4[12];
	result[1] = vec4[0] * mat4[1] + vec4[1] * mat4[5] + vec4[2] * mat4[9] + vec4[3] * mat4[13];
	result[2] = vec4[0] * mat4[2] + vec4[1] * mat4[6] + vec4[2] * mat4[10] + vec4[3] * mat4[14];
	result[3] = vec4[0] * mat4[3] + vec4[1] * mat4[7] + vec4[2] * mat4[11] + vec4[3] * mat4[15];
	return result;
}

static float4 vec3MULFloat(float4 vec4, float scalar) {
	float4 result = vec4;
	result[0]*= scalar;
	result[1]*= scalar;
	result[2]*= scalar;
	return result;
}

static float4 vec3ADDFloat(float4 vec41, float4 vec42) {
	float4 result = vec41;
	result[0]+= vec42[0];
	result[1]+= vec42[1];
	result[2]+= vec42[2];
	return result;
}

kernel void computeSkinning(
	global float* inVertexFloatArray,
	global float* inNormalFloatArray,
	global int* inSkinningVertexJoints,
	global int* inSkinningVertexJointIdxs,
	global float* inSkinningVertexJointWeights,
	global float* outVertexFloatArray,
	global float* outNormalFloatArray,
	global float16* inSkinningJointsTransformationsMatrices,
	const int vertexCount,
	const int matrixCount,
	const int instanceCount
	) {
	// TODO: tangents and bitangents
	int vertexOffset = int(get_global_id(0) * get_local_size(0) + get_local_id(0));
	int instance = int(get_global_id(1) * get_local_size(1) + get_local_id(1));
	if (instance < instanceCount && vertexOffset < vertexCount) {
		float4 skinnedVertex = float4(0.0, 0.0, 0.0, 1.0);
		float4 skinnedNormal = float4(0.0, 0.0, 0.0, 0.0);
		float totalWeights = 0.0;
		float4 inVertex = float4(inVertexFloatArray[vertexOffset * 3 + 0], inVertexFloatArray[vertexOffset * 3 + 1], inVertexFloatArray[vertexOffset * 3 + 2], 1.0);
		float4 inNormal = float4(inNormalFloatArray[vertexOffset * 3 + 0], inNormalFloatArray[vertexOffset * 3 + 1], inNormalFloatArray[vertexOffset * 3 + 2], 0.0);
		for (int i = 0; i < inSkinningVertexJoints[vertexOffset]; i++) {
			float16 transformationsMatrix = inSkinningJointsTransformationsMatrices[instance * matrixCount + inSkinningVertexJointIdxs[vertexOffset * 4 + i]];
			skinnedVertex = vec3ADDFloat(skinnedVertex, vec3MULFloat(mat4MULvec4(transformationsMatrix, inVertex), inSkinningVertexJointWeights[vertexOffset * 4 + i]));
			skinnedNormal = vec3ADDFloat(skinnedNormal, vec3MULFloat(mat4MULvec4(transformationsMatrix, inNormal), inSkinningVertexJointWeights[vertexOffset * 4 + i]));
			totalWeights+= inSkinningVertexJointWeights[vertexOffset * 4 + i];
		}
		if (totalWeights != 1.0) {
			float weightNormalized = totalWeights != 0.0?1.0 / totalWeights:0.0;
			skinnedVertex = vec3MULFloat(skinnedVertex, weightNormalized);
			skinnedNormal = vec3MULFloat(skinnedNormal, weightNormalized);
		}
		outVertexFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 0] = skinnedVertex[0];
		outVertexFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 1] = skinnedVertex[1];
		outVertexFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 2] = skinnedVertex[2];
		outNormalFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 0] = skinnedNormal[0];
		outNormalFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 1] = skinnedNormal[1];
		outNormalFloatArray[instance * vertexCount * 3 + vertexOffset * 3 + 2] = skinnedNormal[2];
	}
}
