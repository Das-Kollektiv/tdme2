vec3 computeWorldPosition(vec4 vertex, mat4 shaderTransformMatrix) {
	// transformations matrices
	mat4 worldMatrix = inModelMatrix * shaderTransformMatrix;
	vec4 worldPosition = worldMatrix * vertex;
	return (worldPosition.xyz / worldPosition.w).xyz;
}

void computeVertex(vec4 vertex, vec3 normal, mat4 shaderTransformMatrix) {
	// transformations matrices
	mat4 mvMatrix = cameraMatrix * inModelMatrix * shaderTransformMatrix;
	mat4 mvpMatrix = projectionMatrix * cameraMatrix * inModelMatrix * shaderTransformMatrix;
	mat4 normalMatrix = mat4(transpose(inverse(mat3(cameraMatrix * inModelMatrix * shaderTransformMatrix))));

	// texure UV
	vsFragTextureUV = vec2(textureMatrix * vec3(inTextureUV, 1.0));

	// compute the normal
	vsNormal = normalize(vec3(normalMatrix * vec4(normal, 0.0)));

	// normal texture
	if (normalTextureAvailable == 1) {
		vsTangent = normalize(vec3(normalMatrix * vec4(inTangent, 0.0)));
		vsBitangent = normalize(vec3(normalMatrix * vec4(inBitangent, 0.0)));
	} else {
		vsTangent = vec3(0.0, 0.0, 0.0);
		vsBitangent = vec3(0.0, 0.0, 0.0);
	}

	// effect colors
	vsEffectColorMul = inEffectColorMul;
	vsEffectColorAdd = inEffectColorAdd;

	// gl position
	vec4 vsPosition4 = mvMatrix * vertex;
	gl_Position = mvpMatrix * vertex;
	vsPosition = vsPosition4.xyz / vsPosition4.w;
}
