// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Arrays_ArrayList.h>

using java::util::Arrays_ArrayList;
extern void unimplemented_(const char16_t* name);
java::util::Arrays_ArrayList::Arrays_ArrayList(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::Arrays_ArrayList::Arrays_ArrayList(ObjectArray* arg0)
	: Arrays_ArrayList(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

constexpr int64_t java::util::Arrays_ArrayList::serialVersionUID;

void Arrays_ArrayList::ctor(ObjectArray* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Arrays_ArrayList::ctor(ObjectArray* arg0)");
}

bool Arrays_ArrayList::contains(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Arrays_ArrayList::contains(Object* arg0)");
	return 0;
}

Object* Arrays_ArrayList::get(int32_t arg0)
{ /* stub */
	unimplemented_(u"Object* Arrays_ArrayList::get(int32_t arg0)");
	return 0;
}

int32_t Arrays_ArrayList::indexOf(Object* arg0)
{ /* stub */
	unimplemented_(u"int32_t Arrays_ArrayList::indexOf(Object* arg0)");
	return 0;
}

Object* Arrays_ArrayList::set(int32_t arg0, Object* arg1)
{ /* stub */
	unimplemented_(u"Object* Arrays_ArrayList::set(int32_t arg0, Object* arg1)");
	return 0;
}

int32_t Arrays_ArrayList::size()
{ /* stub */
	unimplemented_(u"int32_t Arrays_ArrayList::size()");
	return 0;
}

ObjectArray* Arrays_ArrayList::toArray()
{ /* stub */
	unimplemented_(u"ObjectArray* Arrays_ArrayList::toArray()");
	return 0;
}

ObjectArray* Arrays_ArrayList::toArray(ObjectArray* arg0)
{ /* stub */
	unimplemented_(u"ObjectArray* Arrays_ArrayList::toArray(ObjectArray* arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Arrays_ArrayList::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Arrays.ArrayList", 26);
    return c;
}

java::lang::Class* Arrays_ArrayList::getClass0()
{
	return class_();
}

