// Generated from /tdme/src/tdme/utils/Pool.java
#include <tdme/utils/Pool.h>

#include <vector>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/utils/_Console.h>

using std::vector;

using tdme::utils::Pool;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::utils::_Console;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

Pool::Pool(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Pool::Pool() 
	: Pool(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Pool::ctor()
{
	super::ctor();
}

Object* Pool::allocate()
{
	if (freeElements.empty() == false) {
		Object* element = freeElements.at(freeElements.size() - 1);
		freeElements.erase(freeElements.begin() + freeElements.size() - 1);
		usedElements.push_back(element);
		return element;
	}
	auto element = java_cast< Object* >(instantiate());
	usedElements.push_back(element);
	return element;
}

void Pool::release(Object* element)
{
	for (auto i = 0; i < usedElements.size(); i++) {
		if (usedElements.at(i) == element) {
			usedElements.erase(usedElements.begin() + i);
			freeElements.push_back(element);
			return;
		}
	}
	_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Pool::release()::did not find:"_j)->append(element->toString())));
}

int32_t Pool::capacity()
{
	return usedElements.size() + freeElements.size();
}

int32_t Pool::size()
{
	return usedElements.size();
}

void Pool::reset()
{
	for (auto i = 0; i < usedElements.size(); i++) {
		freeElements.push_back(usedElements.at(i));
	}
	usedElements.clear();
}

String* Pool::toString()
{
	return ::java::lang::StringBuilder().append(u"Pool [size="_j)->append(size())
		->append(u", capacity="_j)
		->append(capacity())
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Pool::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.utils.Pool", 15);
    return c;
}

java::lang::Class* Pool::getClass0()
{
	return class_();
}

