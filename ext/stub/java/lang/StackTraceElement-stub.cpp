// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/StackTraceElement.h>

using java::lang::StackTraceElement;
extern void unimplemented_(const char16_t* name);
java::lang::StackTraceElement::StackTraceElement(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::StackTraceElement::StackTraceElement(String* arg0, String* arg1, String* arg2, int32_t arg3)
	: StackTraceElement(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}

constexpr int64_t java::lang::StackTraceElement::serialVersionUID;

void StackTraceElement::ctor(String* arg0, String* arg1, String* arg2, int32_t arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void StackTraceElement::ctor(String* arg0, String* arg1, String* arg2, int32_t arg3)");
}

/* private: bool StackTraceElement::eq(Object* arg0, Object* arg1) */
bool StackTraceElement::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool StackTraceElement::equals(Object* arg0)");
	return 0;
}

String* StackTraceElement::getClassName()
{ /* stub */
	unimplemented_(u"String* StackTraceElement::getClassName()");
	return 0;
}

String* StackTraceElement::getFileName()
{ /* stub */
return fileName ; /* getter */
}

int32_t StackTraceElement::getLineNumber()
{ /* stub */
return lineNumber ; /* getter */
}

String* StackTraceElement::getMethodName()
{ /* stub */
return methodName ; /* getter */
}

int32_t StackTraceElement::hashCode()
{ /* stub */
	unimplemented_(u"int32_t StackTraceElement::hashCode()");
	return 0;
}

bool StackTraceElement::isNativeMethod()
{ /* stub */
	unimplemented_(u"bool StackTraceElement::isNativeMethod()");
	return 0;
}

String* StackTraceElement::toString()
{ /* stub */
	unimplemented_(u"String* StackTraceElement::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* StackTraceElement::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.StackTraceElement", 27);
    return c;
}

java::lang::Class* StackTraceElement::getClass0()
{
	return class_();
}

