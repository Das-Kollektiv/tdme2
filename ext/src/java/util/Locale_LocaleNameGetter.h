// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/spi/fwd-tdme.h>
#include <java/lang/Object.h>
#include <sun/util/LocaleServiceProviderPool_LocalizedObjectGetter.h>

using java::lang::Object;
using sun::util::LocaleServiceProviderPool_LocalizedObjectGetter;
using java::lang::String;
using java::util::Locale;
using java::util::spi::LocaleNameProvider;

using java::lang::ObjectArray;

struct default_init_tag;
class java::util::Locale_LocaleNameGetter
	: public virtual Object
	, public virtual LocaleServiceProviderPool_LocalizedObjectGetter
{

public:
	typedef Object super;

public: /* package */
	static bool $assertionsDisabled;

private:
	static Locale_LocaleNameGetter* INSTANCE;

	/*void ctor(); (private) */

public:
	virtual String* getObject(LocaleNameProvider* arg0, Locale* arg1, String* arg2, ObjectArray* arg3);

	// Generated
	Locale_LocaleNameGetter();
protected:
	Locale_LocaleNameGetter(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual Object* getObject(Object* arg0, Locale* arg1, String* arg2, ObjectArray* arg3) override;

private:
	virtual ::java::lang::Class* getClass0();
};
