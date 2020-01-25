#include <tdme/tests/MathOperatorTest.h>

#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utils/Console.h>

using tdme::tests::MathOperatorTest;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utils::Console;

MathOperatorTest::MathOperatorTest()
{
}

void MathOperatorTest::main()
{
	auto mt = new MathOperatorTest();
	Console::println(string("Math operator tests:"));
	mt->testVector2Operators();
	mt->testVector3Operators();
	mt->testVector4Operators();
}

void MathOperatorTest::testVector2Operators()
{
	Vector2 v1 = Vector2(14.0, 45.3);
	Vector2 v2, v3, v4 = Vector2(0.48, 19.33);
	float f = 3.4;

	Console::println(string("\nVector2 operators\n-----------------"));

	// operator ==
	Console::print(string("operator ==: "));
	if ((v1 == v1) == (v1.equals(v1) )) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator +
	Console::print(string("operator +: "));
	if (v2 + v1 == v3.add(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator -
	v3 = v2;
	Console::print(string("operator -: "));
	if (v2 - v1 == v3.sub(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator *
	v3 = v2;
	Console::print(string("operator *(float): "));
	if (v3 * f == v3.scale(f)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}
	v3 = v2;
	Console::print(string("operator *(Vector2&): "));
	if (v3 * v2 == v3.scale(v2)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator /
	v2 = v4;
	v3 = v4;
	Console::print(string("operator /(float): "));
	if (v2 / f == v3.scale(1.0f / f)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	v2 = v4;
	v3 = v4;
	auto vInverted = Vector2(1.0f / v1[0], 1.0f / v1[1]);
	Console::print(string("operator /(Vector2&): "));
	if ((v2 / v1) == v3.scale(vInverted)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator +=
	v3 = v2;
	Console::print(string("operator +=: "));
	if ((v2 += v1) == v3.add(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator -=
	v2 = v4;
	v3 = v4;
	Console::print(string("operator -=: "));
	if ((v2 -= v1) == v3.sub(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator *=
	v2 = v4;
	v3 = v4;
	Console::print(string("operator *=: "));
	if ((v2 *= v1) == v3.scale(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator /=
	v2 = v4;
	v3 = v4;
	vInverted = Vector2(1.0f / v1[0], 1.0f / v1[1]);
	Console::print(string("operator /=: "));
	if ((v2 /= v1) == v3.scale(vInverted)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}
}

void MathOperatorTest::testVector3Operators()
{
	Vector3 v1 = Vector3(14.0, 45.3, 0.342);
	Vector3 v2, v3, v4 = Vector3(0.48, 19.33, 7.209);
	float f = 3.4;

	Console::println(string("\nVector3 operators\n-----------------"));

	// operator ==
	Console::print(string("operator ==: "));
	if ((v1 == v1) == (v1.equals(v1) )) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator +
	Console::print(string("operator +: "));
	if (v2 + v1 == v3.add(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator -
	v3 = v2;
	Console::print(string("operator -: "));
	if (v2 - v1 == v3.sub(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator *
	v3 = v2;
	Console::print(string("operator *(float): "));
	if (v3 * f == v3.scale(f)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}
	v3 = v2;
	Console::print(string("operator *(Vector3&): "));
	if (v3 * v2 == v3.scale(v2)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator /
	v2 = v4;
	v3 = v4;
	Console::print(string("operator /(float): "));
	if (v2 / f == v3.scale(1.0f / f)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	v2 = v4;
	v3 = v4;
	auto vInverted = Vector3(1.0f / v1[0], 1.0f / v1[1], 1.0f / v1[2]);
	Console::print(string("operator /(Vector3&): "));
	if ((v2 / v1) == v3.scale(vInverted)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator +=
	v3 = v2;
	Console::print(string("operator +=: "));
	if ((v2 += v1) == v3.add(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator -=
	v2 = v4;
	v3 = v4;
	Console::print(string("operator -=: "));
	if ((v2 -= v1) == v3.sub(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator *=
	v2 = v4;
	v3 = v4;
	Console::print(string("operator *=: "));
	if ((v2 *= v1) == v3.scale(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator /=
	v2 = v4;
	v3 = v4;
	vInverted = Vector3(1.0f / v1[0], 1.0f / v1[1], 1.0f / v1[2]);
	Console::print(string("operator /=: "));
	if ((v2 /= v1) == v3.scale(vInverted)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}
}

void MathOperatorTest::testVector4Operators() {
	Vector4 v1 = Vector4(14.0, 45.3, 0.342, 2.43);
	Vector4 v2, v3, v4 = Vector4(0.48, 19.33, 7.209, 5.905);
	float f = 3.4;

	Console::println(string("\nVector4 operators\n-----------------"));

	// operator ==
	Console::print(string("operator ==: "));
	if ((v1 == v1) == (v1.equals(v1) )) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator +
	Console::print(string("operator +: "));
	if (v2 + v1 == v3.add(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator -
	v3 = v2;
	Console::print(string("operator -: "));
	if (v2 - v1 == v3.sub(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator *
	v3 = v2;
	Console::print(string("operator *(float): "));
	if (v3 * f == v3.scale(f)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}
	v3 = v2;
	Console::print(string("operator *(Vector3&): "));
	if (v3 * v2 == v3.scale(v2)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator /
	v2 = v4;
	v3 = v4;
	Console::print(string("operator /(float): "));
	if (v2 / f == v3.scale(1.0f / f)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	v2 = v4;
	v3 = v4;
	auto vInverted = Vector4(1.0f / v1[0], 1.0f / v1[1], 1.0f / v1[2], 1.0f / v1[3]);
	Console::print(string("operator /(Vector3&): "));
	if ((v2 / v1) == v3.scale(vInverted)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator +=
	v3 = v2;
	Console::print(string("operator +=: "));
	if ((v2 += v1) == v3.add(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator -=
	v2 = v4;
	v3 = v4;
	Console::print(string("operator -=: "));
	if ((v2 -= v1) == v3.sub(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator *=
	v2 = v4;
	v3 = v4;
	Console::print(string("operator *=: "));
	if ((v2 *= v1) == v3.scale(v1)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}

	// operator /=
	v2 = v4;
	v3 = v4;
	vInverted = Vector4(1.0f / v1[0], 1.0f / v1[1], 1.0f / v1[2], 1.0f / v1[3]);
	Console::print(string("operator /=: "));
	if ((v2 /= v1) == v3.scale(vInverted)) {
		Console::println(string(this->success));
	} else {
		Console::println(string(this->fail));
	}
}
