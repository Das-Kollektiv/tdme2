// Generated from /tdme/src/tdme/tests/AngleTest.java
#include <tdme/tests/AngleTest.h>

#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>

using tdme::tests::AngleTest;
using tdme::math::Vector3;
using tdme::utils::_Console;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

AngleTest::AngleTest() 
{
}

void AngleTest::main(StringArray* args)
{
	auto a = (new Vector3(0.0f, 0.0f, 1.0f))->normalize();
	auto b = (new Vector3(-1.0f, 0.0f, +1.0f))->normalize();
	auto n = new Vector3(0.0f, 1.0f, 0.0f);
	_Console::println(Vector3::computeAngle(a, b, n));
}
