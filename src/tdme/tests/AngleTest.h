// Generated from /tdme/src/tdme/tests/AngleTest.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>

using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;

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

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

class tdme::tests::AngleTest
{
public:
	static void main(StringArray* args);

	// Generated
	AngleTest();
};
