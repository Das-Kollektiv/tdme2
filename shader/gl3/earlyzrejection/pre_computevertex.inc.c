void computeVertex(vec4 vertex, int inArrayIndex, mat4 shaderTransformMatrix) {
	// transformations matrices
	mat4 mvMatrix = cameraMatrix * GS_IN_ARRAY_AT(vsModelMatrix, inArrayIndex) * shaderTransformMatrix;
	mat4 mvpMatrix = projectionMatrix * cameraMatrix * GS_IN_ARRAY_AT(vsModelMatrix, inArrayIndex) * shaderTransformMatrix;
	mat4 normalMatrix = mat4(transpose(inverse(mat3(cameraMatrix * GS_IN_ARRAY_AT(vsModelMatrix, inArrayIndex) * shaderTransformMatrix))));

	// texure UV
	gsFragTextureUV = vec2(textureMatrix * vec3(GS_IN_ARRAY_AT(vsFragTextureUV, inArrayIndex), 1.0));

	// gl position
	gl_Position = mvpMatrix * vertex;
}
