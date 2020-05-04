mat4 createRotationMatrix(vec3 axis, float angle) {
    float c = cos(angle * 0.017453294);
    float s = sin(angle * 0.017453294);
    float c1 = 1.0 - c;
    return mat4(
		axis[0] * axis[0] * c1 + c,
		axis[0] * axis[1] * c1 + axis[2] * s,
		axis[0] * axis[2] * c1 - axis[1] * s,
		0.0,
		axis[0] * axis[1] * c1 - axis[2] * s,
		axis[1] * axis[1] * c1 + c,
		axis[1] * axis[2] * c1 + axis[0] * s,
		0.0,
		axis[0] * axis[2] * c1 + axis[1] * s,
		axis[1] * axis[2] * c1 - axis[0] * s,
		axis[2] * axis[2] * c1 + c,
		0.0,
		0.0,
		0.0,
		0.0,
		1.0
	);
}
