// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/logging/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;
class java::util::logging::Logger_SystemLoggerHelper
	: public virtual Object
{

public:
	typedef Object super;

public: /* package */
	static bool disableCallerCheck;

	/*void ctor(); (private) */
	/*static bool getBooleanProperty(String* arg0); (private) */

	// Generated

public:
	Logger_SystemLoggerHelper();
protected:
	Logger_SystemLoggerHelper(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
