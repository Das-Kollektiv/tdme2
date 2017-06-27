// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/nativewindow/VisualIDHolder_VIDComparator.h>

#include <com/jogamp/nativewindow/VisualIDHolder.h>

using com::jogamp::nativewindow::VisualIDHolder_VIDComparator;
using com::jogamp::nativewindow::VisualIDHolder;

extern void unimplemented_(const char16_t* name);
com::jogamp::nativewindow::VisualIDHolder_VIDComparator::VisualIDHolder_VIDComparator(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::nativewindow::VisualIDHolder_VIDComparator::VisualIDHolder_VIDComparator(VisualIDHolder_VIDType* arg0)
	: VisualIDHolder_VIDComparator(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void VisualIDHolder_VIDComparator::ctor(VisualIDHolder_VIDType* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void VisualIDHolder_VIDComparator::ctor(VisualIDHolder_VIDType* arg0)");
}

int32_t VisualIDHolder_VIDComparator::compare(VisualIDHolder* arg0, VisualIDHolder* arg1)
{ /* stub */
	unimplemented_(u"int32_t VisualIDHolder_VIDComparator::compare(VisualIDHolder* arg0, VisualIDHolder* arg1)");
	return 0;
}

int32_t VisualIDHolder_VIDComparator::compare(Object* o1, Object* o2)
{ 
	return compare(dynamic_cast< VisualIDHolder* >(o1), dynamic_cast< VisualIDHolder* >(o2));
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* VisualIDHolder_VIDComparator::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.nativewindow.VisualIDHolder.VIDComparator", 52);
    return c;
}

bool VisualIDHolder_VIDComparator::equals(Object* obj)
{
	return Object::equals(obj);
}

java::lang::Class* VisualIDHolder_VIDComparator::getClass0()
{
	return class_();
}

