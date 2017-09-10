#include <tdme/tests/AngleTest.h>

#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>

using tdme::tests::AngleTest;
using tdme::math::Vector3;
using tdme::utils::_Console;

void AngleTest::main()
{
	auto a = (new Vector3(0.0f, 0.0f, 1.0f))->normalize();
	auto b = (new Vector3(-1.0f, 0.0f, +1.0f))->normalize();
	auto n = new Vector3(0.0f, 1.0f, 0.0f);
	_Console::println(Vector3::computeAngle(a, b, n));
}
