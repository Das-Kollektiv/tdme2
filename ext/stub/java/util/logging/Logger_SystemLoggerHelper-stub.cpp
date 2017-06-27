// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/logging/Logger_SystemLoggerHelper.h>

using java::util::logging::Logger_SystemLoggerHelper;
extern void unimplemented_(const char16_t* name);
java::util::logging::Logger_SystemLoggerHelper::Logger_SystemLoggerHelper(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

bool java::util::logging::Logger_SystemLoggerHelper::disableCallerCheck;

/* private: void Logger_SystemLoggerHelper::ctor() */
/* private: bool Logger_SystemLoggerHelper::getBooleanProperty(String* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Logger_SystemLoggerHelper::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.logging.Logger.SystemLoggerHelper", 43);
    return c;
}

java::lang::Class* Logger_SystemLoggerHelper::getClass0()
{
	return class_();
}

