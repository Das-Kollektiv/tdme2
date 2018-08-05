mat4 createTranslationMatrix(vec3 translation) {
	return mat4(
		1.0,
		0.0,
		0.0,
		0.0,
		0.0,
		1.0,
		0.0,
		0.0,
		0.0,
		0.0,
		1.0,
		0.0,
		translation[0],
		translation[1],
		translation[2],
		1.0
	);
}
