// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Throwable.h>

using java::lang::Throwable;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::StackTraceElement, ObjectArray, ::java::io::SerializableArray > StackTraceElementArray;
}  // namespace lang
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::lang::Throwable::Throwable(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::Throwable::Throwable()
	: Throwable(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::Throwable::Throwable(String* arg0)
	: Throwable(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::Throwable::Throwable(Throwable* arg0)
	: Throwable(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::Throwable::Throwable(String* arg0, Throwable* arg1)
	: Throwable(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int64_t java::lang::Throwable::serialVersionUID;

void Throwable::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Throwable::ctor()");
}

void Throwable::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Throwable::ctor(String* arg0)");
}

void Throwable::ctor(Throwable* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Throwable::ctor(Throwable* arg0)");
}

void Throwable::ctor(String* arg0, Throwable* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Throwable::ctor(String* arg0, Throwable* arg1)");
}

Throwable* Throwable::getCause()
{ /* stub */
return cause ; /* getter */
}

String* Throwable::getLocalizedMessage()
{ /* stub */
	unimplemented_(u"String* Throwable::getLocalizedMessage()");
	return 0;
}

String* Throwable::getMessage()
{ /* stub */
	unimplemented_(u"String* Throwable::getMessage()");
	return 0;
}

/* private: StackTraceElementArray* Throwable::getOurStackTrace() */
StackTraceElementArray* Throwable::getStackTrace()
{ /* stub */
return stackTrace ; /* getter */
}

Throwable* Throwable::initCause(Throwable* arg0)
{ /* stub */
	unimplemented_(u"Throwable* Throwable::initCause(Throwable* arg0)");
	return 0;
}

void Throwable::printStackTrace()
{ /* stub */
	unimplemented_(u"void Throwable::printStackTrace()");
}

void Throwable::printStackTrace(PrintStream* arg0)
{ /* stub */
	unimplemented_(u"void Throwable::printStackTrace(PrintStream* arg0)");
}

void Throwable::printStackTrace(PrintWriter* arg0)
{ /* stub */
	unimplemented_(u"void Throwable::printStackTrace(PrintWriter* arg0)");
}

/* private: void Throwable::printStackTraceAsCause(PrintStream* arg0, StackTraceElementArray* arg1) */
/* private: void Throwable::printStackTraceAsCause(PrintWriter* arg0, StackTraceElementArray* arg1) */
void Throwable::setStackTrace(StackTraceElementArray* arg0)
{ /* stub */
	this->stackTrace = arg0; /* setter */
}

String* Throwable::toString()
{ /* stub */
	unimplemented_(u"String* Throwable::toString()");
	return 0;
}

/* private: void Throwable::writeObject(ObjectOutputStream* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Throwable::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Throwable", 19);
    return c;
}

java::lang::Class* Throwable::getClass0()
{
	return class_();
}

