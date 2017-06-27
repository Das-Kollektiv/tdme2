// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::Integer;
using java::lang::Number;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::Number, ObjectArray, ::java::io::SerializableArray > NumberArray;
typedef ::SubArray< ::java::lang::Integer, NumberArray, ComparableArray > IntegerArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::IntegerArray;
using java::lang::NumberArray;
using java::lang::ObjectArray;

struct default_init_tag;
class java::lang::Integer_IntegerCache
	: public virtual Object
{

public:
	typedef Object super;

public: /* package */
	static IntegerArray* cache;
	static int32_t high;

	/*void ctor(); (private) */

	// Generated

public:
	Integer_IntegerCache();
protected:
	Integer_IntegerCache(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
