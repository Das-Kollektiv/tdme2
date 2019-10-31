void computeVertex(vec4 vertex, vec3 normal, mat4 shaderTransformMatrix) {
	// transformation matrices
	mat4 mvMatrix = cameraMatrix * inModelMatrix * shaderTransformMatrix;
	mat4 mvpMatrix = projectionMatrix * cameraMatrix * inModelMatrix * shaderTransformMatrix;
	mat4 normalMatrix = mat4(transpose(inverse(mat3(cameraMatrix * inModelMatrix * shaderTransformMatrix))));

	// texure UV
	vsFragTextureUV = vec2(textureMatrix * vec3(vsFragTextureUV, 1.0));

	// shadow coord
	vsShadowCoord = depthBiasMVPMatrix * inModelMatrix * shaderTransformMatrix * vertex;
	vsShadowCoord = vsShadowCoord / vsShadowCoord.w;

	// shadow intensity
	vec3 normalTransformed = normalize(vec3(normalMatrix * vec4((normal), 0.0)));
	vsShadowIntensity = clamp(abs(dot(normalize(lightDirection.xyz), normalTransformed)), 0.0, 1.0);

	// eye coordinate position of vertex, needed in various calculations
	vec4 vsPosition4 = mvMatrix * vertex;
	vsPosition = vsPosition4.xyz / vsPosition4.w;

	// compute gl position
	gl_Position = mvpMatrix * vertex;
	gl_Position.z-= 0.0001;
}
