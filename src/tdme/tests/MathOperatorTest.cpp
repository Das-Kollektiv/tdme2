#include <tdme/tests/MathOperatorTest.h>

#include <tdme/math/Vector2.h>
#include <tdme/utils/Console.h>

using tdme::tests::MathOperatorTest;
using tdme::math::Vector2;
using tdme::utils::Console;

MathOperatorTest::MathOperatorTest()
{
}

void MathOperatorTest::main()
{
	auto mt = new MathOperatorTest();
	Console::println(string("Math operator tests:\n"));
	mt->testVector2Operators();
}

void MathOperatorTest::testVector2Operators()
{
	Vector2 v1 = Vector2(14.0, 45.3);
	Vector2 v2, v3, v4 = Vector2(0.48, 19.33);
	float f = 3.4;

	Console::println(string("Vector2 operators\n-----------------"));

	// operator ==
	Console::print(string("operator ==: "));
	if ((v1 == v1) == (v1.equals(v1) )) {
		Console::println(string(this->succes));
	} else {
		Console::println(string(this->fail));
	}

	// operator +
	Console::print(string("operator +: "));
	if (v2 + v1 == v3.add(v1)) {
		Console::println(string(this->succes));
	} else {
		Console::println(string(this->fail));
	}

	// operator -
	v3 = v2;
	Console::print(string("operator -: "));
	if (v2 - v1 == v3.sub(v1)) {
		Console::println(string(this->succes));
	} else {
		Console::println(string(this->fail));
	}

	// operator *
	v3 = v2;
	Console::print(string("operator *(float): "));
	if (v3 * f == v3.scale(f)) {
		Console::println(string(this->succes));
	} else {
		Console::println(string(this->fail));
	}
	v3 = v2;
	Console::print(string("operator *(Vector2&): "));
	if (v3 * v2 == v3.scale(v2)) {
		Console::println(string(this->succes));
	} else {
		Console::println(string(this->fail));
	}

	// operator /
	v2 = v4;
	v3 = v4;
	Console::print(string("operator /(float): "));
	if (v2 / f == v3.scale(1.0f / f)) {
		Console::println(string(this->succes));
	} else {
		Console::println(string(this->fail));
	}

	v2 = v4;
	v3 = v4;
	auto vInverted = Vector2(1.0f / v1[0], 1.0f / v1[1]);
	Console::print(string("operator /(Vector2&): "));
	if ((v2 / v1) == v3.scale(vInverted)) {
		Console::println(string(this->succes));
	} else {
		Console::println(string(this->fail));
	}

	// operator +=
	v3 = v2;
	Console::print(string("operator +=: "));
	if ((v2 += v1) == v3.add(v1)) {
		Console::println(string(this->succes));
	} else {
		Console::println(string(this->fail));
	}

	// operator -=
	v2 = v4;
	v3 = v4;
	Console::print(string("operator -=: "));
	if ((v2 -= v1) == v3.sub(v1)) {
		Console::println(string(this->succes));
	} else {
		Console::println(string(this->fail));
	}

	// operator *=
	v2 = v4;
	v3 = v4;
	Console::print(string("operator *=: "));
	if ((v2 *= v1) == v3.scale(v1)) {
		Console::println(string(this->succes));
	} else {
		Console::println(string(this->fail));
	}

	// operator /=
	v2 = v4;
	v3 = v4;
	vInverted = Vector2(1.0f / v1[0], 1.0f / v1[1]);
	Console::print(string("operator /=: "));
	if ((v2 /= v1) == v3.scale(vInverted)) {
		Console::println(string(this->succes));
	} else {
		Console::println(string(this->fail));
	}
}
