#pragma once

#include <initializer_list>
#include <stdint.h>

#include <java/lang/Object.h>
#include <java/lang/Cloneable.h>
#include <java/io/Serializable.h>

extern java::lang::Class *class_(const char16_t *c, int n);

template<typename T>
class Array
    : public virtual ::java::lang::Object
    , public ::java::lang::Cloneable
    , public ::java::io::Serializable
{
public:
    static ::java::lang::Class *class_();

    typedef T value_type;
    typedef value_type *pointer_type;
    typedef pointer_type iterator;
    typedef const value_type *const_pointer_type;
    typedef const_pointer_type const_iterator;

    typedef int size_type;

    Array() : length(0), p(nullptr) { }
    Array(int n) : length(n), p(n == 0 ? nullptr : new value_type[n])
    {
    	for(auto x = p; x != p + length; ++x) *x = value_type();
    }

    Array(const value_type *values, int n) : length(n), p(new value_type[n])
    {
        auto x = p;
        for(auto v = values; v != values + n; ++v) *x++ = *v;
    }

    template<typename S>
    Array(std::initializer_list<S> l) : length(l.size()), p(new value_type[l.size()])
    {
        auto x = p;
        for(auto v : l) *x++ = v;
    }

    Array(const Array &rhs) : Array(rhs.p, rhs.length) { }

    Array(Array &&rhs) : length(rhs.length), p(rhs.p)
    {
         const_cast<pointer_type&>(rhs.p) = 0;
    }

    Array &operator=(const Array &rhs)
    {
        if(&rhs != this) {
            if(length != rhs.length) {
                delete p;
                const_cast<pointer_type&>(p) = 0;
                const_cast<size_type&>(length) = rhs.length;
                const_cast<pointer_type&>(p) = new value_type[length];
            }

            auto x = p;
            for(auto v = rhs.p; v != rhs.p + rhs.length; ++v) *x++ = *v;
        }

        return *this;
    }

    Array &operator=(Array &&rhs)
    {
        if(&rhs != this) {
            delete p;
            const_cast<size_type&>(length) = rhs.length;
            const_cast<pointer_type&>(p) = rhs.p;
            const_cast<pointer_type&>(rhs.p) = 0;
        }

    	return *this;
    }

    virtual ~Array() { delete p; }

    Array* clone() override { return new Array(*this); }

    value_type operator[](size_type i) const { return p[i]; }
    value_type &operator[](size_type i) { return p[i]; }

    value_type get(size_type i) const { return p[i]; }
    value_type &set(size_type i, value_type x) { return (p[i] = x); }

    iterator        begin() { return p; }
    const_iterator  begin() const { return p; }
    const_iterator  cbegin() const { return begin(); }

    iterator        end() { return p + length; }
    const_iterator  end() const { return p + length; }
    const_iterator  cend() const { return end(); }

    const size_type length;
    const pointer_type p;

private:
    ::java::lang::Class *getClass0() override { return class_(); }
};

typedef Array<bool> boolArray;
typedef Array<char16_t> char16_tArray;
typedef Array<int8_t> int8_tArray;
typedef Array<int16_t> int16_tArray;
typedef Array<int32_t> int32_tArray;
typedef Array<int64_t> int64_tArray;
typedef Array<double> doubleArray;
typedef Array<float> floatArray;

template<>
inline java::lang::Class* boolArray::class_() {
    static ::java::lang::Class* c = ::class_(u"boolean[]", 9);
    return c;
}
template<>
inline java::lang::Class* char16_tArray::class_() {
    static ::java::lang::Class* c = ::class_(u"char[]", 9);
    return c;
}
template<>
inline java::lang::Class* int8_tArray::class_() {
    static ::java::lang::Class* c = ::class_(u"byte[]", 9);
    return c;
}
template<>
inline java::lang::Class* int16_tArray::class_() {
    static ::java::lang::Class* c = ::class_(u"short[]", 9);
    return c;
}
template<>
inline java::lang::Class* int32_tArray::class_() {
    static ::java::lang::Class* c = ::class_(u"int[]", 9);
    return c;
}
template<>
inline java::lang::Class* int64_tArray::class_() {
    static ::java::lang::Class* c = ::class_(u"long[]", 9);
    return c;
}
template<>
inline java::lang::Class* doubleArray::class_() {
    static ::java::lang::Class* c = ::class_(u"double[]", 9);
    return c;
}
template<>
inline java::lang::Class* floatArray::class_() {
    static ::java::lang::Class* c = ::class_(u"float[]", 9);
    return c;
}
