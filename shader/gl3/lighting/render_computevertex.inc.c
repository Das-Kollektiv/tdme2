vec3 computeWorldPosition(vec4 vertex, int inArrayIndex, mat4 shaderTransformMatrix) {
	// transformations matrices
	mat4 worldMatrix = GS_IN_ARRAY_AT(vsModelMatrix, inArrayIndex) * shaderTransformMatrix;
	vec4 worldPosition = worldMatrix * vertex;
	return (worldPosition.xyz / worldPosition.w).xyz;
}

void computeVertex(vec4 vertex, int inArrayIndex, mat4 shaderTransformMatrix) {
	// transformations matrices
	mat4 mvMatrix = cameraMatrix * GS_IN_ARRAY_AT(vsModelMatrix, inArrayIndex) * shaderTransformMatrix;
	mat4 mvpMatrix = projectionMatrix * cameraMatrix * GS_IN_ARRAY_AT(vsModelMatrix, inArrayIndex) * shaderTransformMatrix;
	mat4 normalMatrix = mat4(transpose(inverse(mat3(cameraMatrix * GS_IN_ARRAY_AT(vsModelMatrix, inArrayIndex) * shaderTransformMatrix))));

	// texure UV
	gsFragTextureUV = vec2(textureMatrix * vec3(GS_IN_ARRAY_AT(vsFragTextureUV, inArrayIndex), 1.0));

	// compute the normal
	gsNormal = normalize(vec3(normalMatrix * vec4(GS_IN_ARRAY_AT(vsNormal, inArrayIndex), 0.0)));

	// normal texture
	if (normalTextureAvailable == 1) {
		gsTangent = normalize(vec3(normalMatrix * vec4(GS_IN_ARRAY_AT(vsTangent, inArrayIndex), 0.0)));
		gsBitangent = normalize(vec3(normalMatrix * vec4(GS_IN_ARRAY_AT(vsBitangent, inArrayIndex), 0.0)));
	} else {
		gsTangent = vec3(0.0, 0.0, 0.0);
		gsBitangent = vec3(0.0, 0.0, 0.0);
	}

	// effect colors
	gsEffectColorMul = GS_IN_ARRAY_AT(vsEffectColorMul, inArrayIndex);
	gsEffectColorAdd = GS_IN_ARRAY_AT(vsEffectColorAdd, inArrayIndex);

	// gl position
	vec4 gsPosition4 = mvMatrix * vertex;
	gl_Position = mvpMatrix * vertex;
	gsPosition = gsPosition4.xyz / gsPosition4.w;
}
