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

AngleTest::AngleTest(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

AngleTest::AngleTest() 
	: AngleTest(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void AngleTest::ctor()
{
	super::ctor();
}

void AngleTest::main(StringArray* args)
{
	clinit();
	auto a = (new Vector3(0.0f, 0.0f, 1.0f))->normalize();
	auto b = (new Vector3(-1.0f, 0.0f, +1.0f))->normalize();
	auto n = new Vector3(0.0f, 1.0f, 0.0f);
	_Console::println(Vector3::computeAngle(a, b, n));
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AngleTest::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tests.AngleTest", 20);
    return c;
}

java::lang::Class* AngleTest::getClass0()
{
	return class_();
}

