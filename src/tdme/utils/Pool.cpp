// Generated from /tdme/src/tdme/utils/Pool.java
#include <tdme/utils/Pool.h>

#include <vector>
#include <string>

#include <java/lang/fwd-tdme.h>
#include <java/lang/String.h>
#include <java/lang/Object.h>

#include <tdme/utils/_Console.h>

using std::vector;
using std::wstring;

using java::lang::Object;
using java::lang::String;

using tdme::utils::Pool;
using tdme::utils::_Console;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

Pool::Pool() 
{
}

void Pool::ctor()
{
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
	_Console::println(wstring(L"Pool::release()::did not find:") + element->toString()->getCPPWString());
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
