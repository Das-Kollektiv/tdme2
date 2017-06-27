// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/spi/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::Cloneable;
using java::util::Locale;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
}  // namespace lang

namespace util {
typedef ::SubArray< ::java::util::Locale, ::java::lang::ObjectArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > LocaleArray;
}  // namespace util
}  // namespace java

using java::io::SerializableArray;
using java::lang::CloneableArray;
using java::lang::ObjectArray;
using java::util::LocaleArray;

struct default_init_tag;
class java::util::spi::LocaleServiceProvider
	: public virtual Object
{

public:
	typedef Object super;

protected:
	void ctor();

public:
	virtual LocaleArray* getAvailableLocales() = 0;

	// Generated

public: /* protected */
	LocaleServiceProvider();
protected:
	LocaleServiceProvider(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
