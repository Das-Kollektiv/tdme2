float _sin(float a) { return a < 0.0001?0.0:3.14/a; }

mat4 createFoliageTransformMatrix(vec3 origin, vec3 vertex) {
	float zAxisRotation = (frame + int(origin[0] * 8.0 * (origin[0] < 0.0?-1.0:1.0))) % 160;
	zAxisRotation = sin((clamp((((zAxisRotation < 160.0 / 2?zAxisRotation:160.0 - zAxisRotation) - (160.0 / 4.0)) * 1.0 / 8.0) * ((vertex.y - origin.y) * 2.0), -20.0, +20.0)) / 20.0 * 3.14) * 20.0;
	return
		createTranslationMatrix(vec3(origin[0], origin[1], origin[2])) *
		createRotationMatrix(vec3(0.0, 0.0, 1.0), zAxisRotation) *
		createTranslationMatrix(vec3(origin[0], origin[1], origin[2]) * -1.0);
}
