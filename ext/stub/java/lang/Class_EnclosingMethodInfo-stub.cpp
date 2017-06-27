// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Class_EnclosingMethodInfo.h>

using java::lang::Class_EnclosingMethodInfo;
extern void unimplemented_(const char16_t* name);
java::lang::Class_EnclosingMethodInfo::Class_EnclosingMethodInfo(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

bool java::lang::Class_EnclosingMethodInfo::$assertionsDisabled;

/* private: void Class_EnclosingMethodInfo::ctor(ObjectArray* arg0) */
String* Class_EnclosingMethodInfo::getDescriptor()
{ /* stub */
return descriptor ; /* getter */
}

Class* Class_EnclosingMethodInfo::getEnclosingClass()
{ /* stub */
return enclosingClass ; /* getter */
}

String* Class_EnclosingMethodInfo::getName()
{ /* stub */
return name ; /* getter */
}

bool Class_EnclosingMethodInfo::isConstructor()
{ /* stub */
	unimplemented_(u"bool Class_EnclosingMethodInfo::isConstructor()");
	return 0;
}

bool Class_EnclosingMethodInfo::isMethod()
{ /* stub */
	unimplemented_(u"bool Class_EnclosingMethodInfo::isMethod()");
	return 0;
}

bool Class_EnclosingMethodInfo::isPartial()
{ /* stub */
	unimplemented_(u"bool Class_EnclosingMethodInfo::isPartial()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Class_EnclosingMethodInfo::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Class.EnclosingMethodInfo", 35);
    return c;
}

java::lang::Class* Class_EnclosingMethodInfo::getClass0()
{
	return class_();
}

