void computeVertex(vec4 vertex, mat4 shaderTransformMatrix) {
	// transformations matrices
	mat4 mvpMatrix = projectionMatrix * cameraMatrix * inModelMatrix * shaderTransformMatrix;

	// texure UV
	vsFragTextureUV = vec2(textureMatrix * vec3(inTextureUV, 1.0));

	// gl position
	gl_Position = mvpMatrix * vertex;
}
