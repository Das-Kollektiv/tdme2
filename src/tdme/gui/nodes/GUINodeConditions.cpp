// Generated from /tdme/src/tdme/gui/nodes/GUINodeConditions.java
#include <tdme/gui/nodes/GUINodeConditions.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/utils/_ArrayList.h>

using tdme::gui::nodes::GUINodeConditions;
using java::lang::ClassCastException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::utils::_ArrayList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

GUINodeConditions::GUINodeConditions(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINodeConditions::GUINodeConditions() 
	: GUINodeConditions(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void GUINodeConditions::ctor()
{
	super::ctor();
	this->conditions = new _ArrayList();
}

_ArrayList* GUINodeConditions::getConditions()
{
	return conditions;
}

void GUINodeConditions::add(String* condition)
{
	remove(condition);
	conditions->add(condition);
}

void GUINodeConditions::remove(String* condition)
{
	conditions->remove(condition);
}

void GUINodeConditions::removeAll()
{
	conditions->clear();
}

String* GUINodeConditions::toString()
{
	return ::java::lang::StringBuilder().append(u"GUINodeConditions [conditions="_j)->append(static_cast< Object* >(conditions))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINodeConditions::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINodeConditions", 32);
    return c;
}

java::lang::Class* GUINodeConditions::getClass0()
{
	return class_();
}

