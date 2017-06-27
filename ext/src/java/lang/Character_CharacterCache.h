// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::Character;
using java::lang::Comparable;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::Character, ObjectArray, ::java::io::SerializableArray, ComparableArray > CharacterArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::CharacterArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;

struct default_init_tag;
class java::lang::Character_CharacterCache
	: public virtual Object
{

public:
	typedef Object super;

public: /* package */
	static CharacterArray* cache;

	/*void ctor(); (private) */

	// Generated

public:
	Character_CharacterCache();
protected:
	Character_CharacterCache(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
