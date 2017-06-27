// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/System.h>

using java::lang::System;
extern void unimplemented_(const char16_t* name);
java::lang::System::System(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

std::atomic< Console* > java::lang::System::cons;
PrintStream* java::lang::System::err;
InputStream* java::lang::System::in;
PrintStream* java::lang::System::out;
Properties* java::lang::System::props;
std::atomic< SecurityManager* > java::lang::System::security;

/* private: void System::ctor() */
/* private: void System::adjustPropertiesForBackwardCompatibility(Properties* arg0) */
/* private: void System::checkIO() */
/* private: void System::checkKey(String* arg0) */
String* System::clearProperty(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* System::clearProperty(String* arg0)");
	return 0;
}

Console* System::console()
{ /* stub */
	clinit();
	unimplemented_(u"Console* System::console()");
	return 0;
}

void System::exit(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"void System::exit(int32_t arg0)");
}

void System::gc()
{ /* stub */
	clinit();
	unimplemented_(u"void System::gc()");
}

Class* System::getCallerClass()
{ /* stub */
	clinit();
	unimplemented_(u"Class* System::getCallerClass()");
	return 0;
}

Properties* System::getProperties()
{ /* stub */
	clinit();
	unimplemented_(u"Properties* System::getProperties()");
	return 0;
}

String* System::getProperty(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* System::getProperty(String* arg0)");
	return 0;
}

String* System::getProperty(String* arg0, String* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"String* System::getProperty(String* arg0, String* arg1)");
	return 0;
}

SecurityManager* System::getSecurityManager()
{ /* stub */
	clinit();
	unimplemented_(u"SecurityManager* System::getSecurityManager()");
	return 0;
}

Map* System::getenv()
{ /* stub */
	clinit();
	unimplemented_(u"Map* System::getenv()");
	return 0;
}

String* System::getenv(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* System::getenv(String* arg0)");
	return 0;
}

Channel* System::inheritedChannel()
{ /* stub */
	clinit();
	unimplemented_(u"Channel* System::inheritedChannel()");
	return 0;
}

/* private: void System::initializeSystemClass() */
void System::load(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"void System::load(String* arg0)");
}

void System::loadLibrary(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"void System::loadLibrary(String* arg0)");
}

/* private: InputStream* System::nullInputStream() */
/* private: PrintStream* System::nullPrintStream() */
void System::runFinalization()
{ /* stub */
	clinit();
	unimplemented_(u"void System::runFinalization()");
}

void System::runFinalizersOnExit(bool arg0)
{ /* stub */
	clinit();
	unimplemented_(u"void System::runFinalizersOnExit(bool arg0)");
}

void System::setErr(PrintStream* arg0)
{ /* stub */
	clinit();
	System::err = arg0; /* setter */
}

void System::setIn(InputStream* arg0)
{ /* stub */
	clinit();
	System::in = arg0; /* setter */
}

/* private: void System::setJavaLangAccess() */
void System::setOut(PrintStream* arg0)
{ /* stub */
	clinit();
	System::out = arg0; /* setter */
}

void System::setProperties(Properties* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"void System::setProperties(Properties* arg0)");
}

String* System::setProperty(String* arg0, String* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"String* System::setProperty(String* arg0, String* arg1)");
	return 0;
}

void System::setSecurityManager(SecurityManager* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"void System::setSecurityManager(SecurityManager* arg0)");
}

/* private: void System::setSecurityManager0(SecurityManager* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* System::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.System", 16);
    return c;
}

java::lang::Class* System::getClass0()
{
	return class_();
}

