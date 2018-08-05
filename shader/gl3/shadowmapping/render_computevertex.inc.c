void computeVertex(vec4 vertex, int inArrayIndex, mat4 shaderTransformMatrix) {
	// transformation matrices
	mat4 mvMatrix = cameraMatrix * GS_IN_ARRAY_AT(vsModelMatrix, inArrayIndex) * shaderTransformMatrix;
	mat4 mvpMatrix = projectionMatrix * cameraMatrix * GS_IN_ARRAY_AT(vsModelMatrix, inArrayIndex) * shaderTransformMatrix;
	mat4 normalMatrix = mat4(transpose(inverse(mat3(cameraMatrix * GS_IN_ARRAY_AT(vsModelMatrix, inArrayIndex) * shaderTransformMatrix))));

	// texure UV
	gsFragTextureUV = vec2(textureMatrix * vec3(GS_IN_ARRAY_AT(vsFragTextureUV, inArrayIndex), 1.0));

	// shadow coord
	gsShadowCoord = depthBiasMVPMatrix * GS_IN_ARRAY_AT(vsModelMatrix, inArrayIndex) * shaderTransformMatrix * vertex;
	gsShadowCoord = gsShadowCoord / gsShadowCoord.w;

	// shadow intensity
	vec3 normal = normalize(vec3(normalMatrix * vec4(GS_IN_ARRAY_AT(vsNormal, inArrayIndex), 0.0)));
	gsShadowIntensity = clamp(abs(dot(normalize(lightDirection.xyz), normal)), 0.0, 1.0);

	// eye coordinate position of vertex, needed in various calculations
	vec4 gsPosition4 = mvMatrix * vertex;
	gsPosition = gsPosition4.xyz / gsPosition4.w;

	// compute gl position
	gl_Position = mvpMatrix * vertex;
	gl_Position.z-= 0.0001;
}
