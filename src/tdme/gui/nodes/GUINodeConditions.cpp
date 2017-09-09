// Generated from /tdme/src/tdme/gui/nodes/GUINodeConditions.java
#include <tdme/gui/nodes/GUINodeConditions.h>

#include <algorithm>
#include <vector>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>

using std::vector;

using tdme::gui::nodes::GUINodeConditions;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
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
}

vector<wstring>* GUINodeConditions::getConditions()
{
	return &conditions;
}

void GUINodeConditions::add(const wstring& condition)
{
	remove(condition);
	conditions.push_back(condition);
}

void GUINodeConditions::remove(const wstring& condition)
{
	for (vector<wstring>::iterator i = conditions.begin(); i != conditions.end(); i++) {
		if (condition == *i) {
			conditions.erase(i);
			return;
		}

	}
}

void GUINodeConditions::removeAll()
{
	conditions.clear();
}

String* GUINodeConditions::toString()
{
	// basically copied from method _ArrayList::toString() from src/tdme/utils/_ArrayList.cpp
	// to make this work with the vector<String*> of conditions
	auto conditionsVectorAsString = u"["_j;
	for (auto i = 0; i < conditions.size(); i++) {
		conditionsVectorAsString = ::java::lang::StringBuilder(conditionsVectorAsString).append(conditions[i])->toString();
		if (i < conditions.size() - 1)
			conditionsVectorAsString = ::java::lang::StringBuilder(conditionsVectorAsString).append(u", "_j)->toString();
	}
	conditionsVectorAsString = ::java::lang::StringBuilder(conditionsVectorAsString).append(u"]"_j)->toString();

	return ::java::lang::StringBuilder().append(u"GUINodeConditions [conditions="_j)->append(conditionsVectorAsString)
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

