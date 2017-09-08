#include <stdint.h>

#include <iostream>

#include <java/lang/Class.h>

#include <Array.h>
#include <java/lang/String.h>

using namespace java::lang;

void lock(Object*) { }

void unlock(Object*) { }

String *java::lang::operator "" _j(const char16_t* p, size_t n) {
    auto x = new char16_tArray(p, n);
    auto s = new String(x);
    return s->intern();
}

Class *class_(const char16_t *s, int n) {
    return Class::forName(operator "" _j(s, n));
}

void unimplemented_(const char16_t *name) {
    std::wcerr << "call to unimplemented: ";
    // Not quite right but good enough ;)
    while(*name) std::wcerr << static_cast<wchar_t>(*(name++));
    std::wcerr << std::endl;
}
