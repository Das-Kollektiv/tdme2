mat4 createFoliageTransformMatrix(vec3 origin, vec4 vertex) {
	float zAxisRotation = (sin(frame * 3.14*2.0)  + int(origin[0] * 8.0 * (origin[0] < 0.0?-1.0:1.0))) % 160;
	zAxisRotation = (((zAxisRotation < 160 / 2?zAxisRotation:160 - zAxisRotation) - (160 / 4)) * 1.0f / 8.0f);
	return
		createTranslationMatrix(vec3(origin[0], origin[1], origin[2])) *
		createRotationMatrix(vec3(0.0, 0.0, 1.0), zAxisRotation) *
		createTranslationMatrix(vec3(origin[0], origin[1], origin[2]) * -1.0);
}
