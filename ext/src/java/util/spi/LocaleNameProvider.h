// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/spi/fwd-tdme.h>
#include <java/util/spi/LocaleServiceProvider.h>

using java::util::spi::LocaleServiceProvider;
using java::lang::String;
using java::util::Locale;


struct default_init_tag;
class java::util::spi::LocaleNameProvider
	: public LocaleServiceProvider
{

public:
	typedef LocaleServiceProvider super;

protected:
	void ctor();

public:
	virtual String* getDisplayCountry(String* arg0, Locale* arg1) = 0;
	virtual String* getDisplayLanguage(String* arg0, Locale* arg1) = 0;
	virtual String* getDisplayVariant(String* arg0, Locale* arg1) = 0;

	// Generated

public: /* protected */
	LocaleNameProvider();
protected:
	LocaleNameProvider(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
