// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/logging/Logger.h>

using java::util::logging::Logger;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace util {
namespace logging {
typedef ::SubArray< ::java::util::logging::Handler, ::java::lang::ObjectArray > HandlerArray;
}  // namespace logging
}  // namespace util
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::util::logging::Logger::Logger(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::logging::Logger::Logger(String* arg0, String* arg1)
	: Logger(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

String* java::util::logging::Logger::GLOBAL_LOGGER_NAME;
String* java::util::logging::Logger::SYSTEM_LOGGER_RB_NAME;
HandlerArray* java::util::logging::Logger::emptyHandlers;
Logger* java::util::logging::Logger::global;
int32_t java::util::logging::Logger::offValue;
Object* java::util::logging::Logger::treeLock;

/* private: void Logger::ctor(String* arg0) */
void Logger::ctor(String* arg0, String* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Logger::ctor(String* arg0, String* arg1)");
}

void Logger::addHandler(Handler* arg0)
{ /* stub */
	unimplemented_(u"void Logger::addHandler(Handler* arg0)");
}

/* private: void Logger::checkPermission() */
void Logger::config(String* arg0)
{ /* stub */
	unimplemented_(u"void Logger::config(String* arg0)");
}

/* private: Logger* Logger::demandLogger(String* arg0, String* arg1) */
/* private: void Logger::doLog(LogRecord* arg0) */
/* private: void Logger::doLog(LogRecord* arg0, String* arg1) */
/* private: void Logger::doSetParent(Logger* arg0) */
void Logger::entering(String* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"void Logger::entering(String* arg0, String* arg1)");
}

void Logger::entering(String* arg0, String* arg1, Object* arg2)
{ /* stub */
	unimplemented_(u"void Logger::entering(String* arg0, String* arg1, Object* arg2)");
}

void Logger::entering(String* arg0, String* arg1, ObjectArray* arg2)
{ /* stub */
	unimplemented_(u"void Logger::entering(String* arg0, String* arg1, ObjectArray* arg2)");
}

void Logger::exiting(String* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"void Logger::exiting(String* arg0, String* arg1)");
}

void Logger::exiting(String* arg0, String* arg1, Object* arg2)
{ /* stub */
	unimplemented_(u"void Logger::exiting(String* arg0, String* arg1, Object* arg2)");
}

/* private: ResourceBundle* Logger::findResourceBundle(String* arg0) */
/* private: ResourceBundle* Logger::findSystemResourceBundle(Locale* arg0) */
void Logger::fine(String* arg0)
{ /* stub */
	unimplemented_(u"void Logger::fine(String* arg0)");
}

void Logger::finer(String* arg0)
{ /* stub */
	unimplemented_(u"void Logger::finer(String* arg0)");
}

void Logger::finest(String* arg0)
{ /* stub */
	unimplemented_(u"void Logger::finest(String* arg0)");
}

Logger* Logger::getAnonymousLogger()
{ /* stub */
	clinit();
	unimplemented_(u"Logger* Logger::getAnonymousLogger()");
	return 0;
}

Logger* Logger::getAnonymousLogger(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Logger* Logger::getAnonymousLogger(String* arg0)");
	return 0;
}

/* private: String* Logger::getEffectiveResourceBundleName() */
Filter* Logger::getFilter()
{ /* stub */
return filter ; /* getter */
}

HandlerArray* Logger::getHandlers()
{ /* stub */
}

Level* Logger::getLevel()
{ /* stub */
	unimplemented_(u"Level* Logger::getLevel()");
	return 0;
}

Logger* Logger::getLogger(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Logger* Logger::getLogger(String* arg0)");
	return 0;
}

Logger* Logger::getLogger(String* arg0, String* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"Logger* Logger::getLogger(String* arg0, String* arg1)");
	return 0;
}

String* Logger::getName()
{ /* stub */
return name ; /* getter */
}

Logger* Logger::getParent()
{ /* stub */
return parent ; /* getter */
}

ResourceBundle* Logger::getResourceBundle()
{ /* stub */
	unimplemented_(u"ResourceBundle* Logger::getResourceBundle()");
	return 0;
}

String* Logger::getResourceBundleName()
{ /* stub */
return resourceBundleName ; /* getter */
}

bool Logger::getUseParentHandlers()
{ /* stub */
return useParentHandlers ; /* getter */
}

void Logger::info(String* arg0)
{ /* stub */
	unimplemented_(u"void Logger::info(String* arg0)");
}

bool Logger::isLoggable(Level* arg0)
{ /* stub */
	unimplemented_(u"bool Logger::isLoggable(Level* arg0)");
	return 0;
}

void Logger::log(LogRecord* arg0)
{ /* stub */
	unimplemented_(u"void Logger::log(LogRecord* arg0)");
}

void Logger::log(Level* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"void Logger::log(Level* arg0, String* arg1)");
}

void Logger::log(Level* arg0, String* arg1, Object* arg2)
{ /* stub */
	unimplemented_(u"void Logger::log(Level* arg0, String* arg1, Object* arg2)");
}

void Logger::log(Level* arg0, String* arg1, ObjectArray* arg2)
{ /* stub */
	unimplemented_(u"void Logger::log(Level* arg0, String* arg1, ObjectArray* arg2)");
}

void Logger::log(Level* arg0, String* arg1, Throwable* arg2)
{ /* stub */
	unimplemented_(u"void Logger::log(Level* arg0, String* arg1, Throwable* arg2)");
}

void Logger::logp(Level* arg0, String* arg1, String* arg2, String* arg3)
{ /* stub */
	unimplemented_(u"void Logger::logp(Level* arg0, String* arg1, String* arg2, String* arg3)");
}

void Logger::logp(Level* arg0, String* arg1, String* arg2, String* arg3, Object* arg4)
{ /* stub */
	unimplemented_(u"void Logger::logp(Level* arg0, String* arg1, String* arg2, String* arg3, Object* arg4)");
}

void Logger::logp(Level* arg0, String* arg1, String* arg2, String* arg3, ObjectArray* arg4)
{ /* stub */
	unimplemented_(u"void Logger::logp(Level* arg0, String* arg1, String* arg2, String* arg3, ObjectArray* arg4)");
}

void Logger::logp(Level* arg0, String* arg1, String* arg2, String* arg3, Throwable* arg4)
{ /* stub */
	unimplemented_(u"void Logger::logp(Level* arg0, String* arg1, String* arg2, String* arg3, Throwable* arg4)");
}

void Logger::logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4)
{ /* stub */
	unimplemented_(u"void Logger::logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4)");
}

void Logger::logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4, Object* arg5)
{ /* stub */
	unimplemented_(u"void Logger::logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4, Object* arg5)");
}

void Logger::logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4, ObjectArray* arg5)
{ /* stub */
	unimplemented_(u"void Logger::logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4, ObjectArray* arg5)");
}

void Logger::logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4, Throwable* arg5)
{ /* stub */
	unimplemented_(u"void Logger::logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4, Throwable* arg5)");
}

void Logger::removeChildLogger(LogManager_LoggerWeakRef* arg0)
{ /* stub */
	unimplemented_(u"void Logger::removeChildLogger(LogManager_LoggerWeakRef* arg0)");
}

void Logger::removeHandler(Handler* arg0)
{ /* stub */
	unimplemented_(u"void Logger::removeHandler(Handler* arg0)");
}

void Logger::setFilter(Filter* arg0)
{ /* stub */
	this->filter = arg0; /* setter */
}

void Logger::setLevel(Level* arg0)
{ /* stub */
	unimplemented_(u"void Logger::setLevel(Level* arg0)");
}

void Logger::setLogManager(LogManager* arg0)
{ /* stub */
	unimplemented_(u"void Logger::setLogManager(LogManager* arg0)");
}

void Logger::setParent(Logger* arg0)
{ /* stub */
	this->parent = arg0; /* setter */
}

void Logger::setUseParentHandlers(bool arg0)
{ /* stub */
	this->useParentHandlers = arg0; /* setter */
}

/* private: void Logger::setupResourceInfo(String* arg0) */
void Logger::severe(String* arg0)
{ /* stub */
	unimplemented_(u"void Logger::severe(String* arg0)");
}

void Logger::throwing(String* arg0, String* arg1, Throwable* arg2)
{ /* stub */
	unimplemented_(u"void Logger::throwing(String* arg0, String* arg1, Throwable* arg2)");
}

/* private: void Logger::updateEffectiveLevel() */
void Logger::warning(String* arg0)
{ /* stub */
	unimplemented_(u"void Logger::warning(String* arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Logger::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.logging.Logger", 24);
    return c;
}

java::lang::Class* Logger::getClass0()
{
	return class_();
}

