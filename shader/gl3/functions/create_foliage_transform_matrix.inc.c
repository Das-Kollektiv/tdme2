mat4 createFoliageTransformMatrix(vec3 origin, vec3 vertex, vec3 translation) {
	float zAxisRotation = (int(time * 60.0) + int((origin.x + translation.x) * 8.0 * (translation.x + origin.x < 0.0?-1.0:1.0))) % 160;
	zAxisRotation = sin((clamp((((zAxisRotation < 160.0 / 2?zAxisRotation:160.0 - zAxisRotation) - (160.0 / 4.0)) * 1.0 / 8.0) * ((vertex.y - origin.y) * 2.0), -20.0, +20.0)) / 20.0 * 3.14) * 20.0;
	return
		createTranslationMatrix(vec3(origin.x, origin.y, origin.z)) *
		createRotationMatrix(vec3(0.0, 0.0, 1.0), zAxisRotation) *
		createTranslationMatrix(vec3(origin.x, origin.y, origin.z) * -1.0);
}
