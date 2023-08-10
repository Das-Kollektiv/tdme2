#pragma once

#include <array>
#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>

#include <tdme/tdme.h>

using std::array;
using std::forward_iterator_tag;
using std::ptrdiff_t;
using std::unique_ptr;
using std::vector;

namespace tdme {
namespace utilities {

/**
 * Iterator for sequence container iterator
 * @author Andreas Drewke
 */
template<typename T, typename V>
struct Iterator
{
	// see_ https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
	using iterator_category = forward_iterator_tag;
	using difference_type = ptrdiff_t;
	using value_type = V*;
	using pointer = V*;
	using reference = V*;

	// constructor
	Iterator(T* ptr) : ptr(ptr) {}

	// iterator constructors here...
	reference operator*() { return ptr->get(); }
	pointer operator->() { return ptr->get(); }

	// prefix increment
	Iterator<T, V>& operator++() { ptr++; return *this; }

	// postfix increment
	Iterator<T, V> operator++(int) { auto tmp = *this; ++(*this); return tmp; }

	// comparison iterators
	friend bool operator== (const Iterator<T, V>& a, const Iterator<T, V>& b) { return a.ptr == b.ptr; };
	friend bool operator!= (const Iterator<T, V>& a, const Iterator<T, V>& b) { return a.ptr != b.ptr; };

private:
	T* ptr;
};

/**
 * Sequence container iterator
 * @author Andreas Drewke
 */
template<typename T>
struct SequenceContainerIterator {
	SequenceContainerIterator(unique_ptr<T>* containerBegin, unique_ptr<T>* containerEnd): containerBegin(containerBegin), containerEnd(containerEnd) {}
	Iterator<unique_ptr<T>, T> begin() { return Iterator<unique_ptr<T>, T>(containerBegin); }
	Iterator<unique_ptr<T>, T> end()   { return Iterator<unique_ptr<T>, T>(containerEnd); }
private:
	unique_ptr<T>* containerBegin;
	unique_ptr<T>* containerEnd;
};

};
};

