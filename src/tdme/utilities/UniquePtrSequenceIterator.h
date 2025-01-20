#pragma once

#include <cstddef>
#include <iterator>
#include <memory>


using std::forward_iterator_tag;
using std::ptrdiff_t;
using std::unique_ptr;

namespace tdme {
namespace utilities {

/**
 * unique_ptr sequence iterator
 * @author Andreas Drewke
 */
template<typename T>
struct UniquePtrSequenceIterator {

	/**
	 * Iterator for unique_ptr sequence iterator
	 * @author Andreas Drewke
	 */
	template<typename IT, typename IV>
	struct Iterator
	{
		// see: https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
		using iterator_category = forward_iterator_tag;
		using difference_type = ptrdiff_t;
		using value_type = IV*;
		using pointer = IV*;
		using reference = IV*;

		/**
		 * Constructor
		 * @param ptr pointer to container element
		 */
		inline Iterator(IT* ptr) : ptr(ptr) {}

		/**
		 * @returns access iterator '*'
		 */
		inline reference operator*() { return ptr->get(); }

		/**
		 * @returns access iterator '->'
		 */
		inline pointer operator->() { return ptr->get(); }

		/**
		 * @returns prefix incremented iterator
		 */
		inline Iterator<IT, IV>& operator++() { ptr++; return *this; }

		/**
		 * @returns postfix incremented iterator
		 */
		inline Iterator<IT, IV> operator++(int) { auto tmp = *this; ++(*this); return tmp; }

		/**
		 * Equality comparison operator
		 * @param a a iterator
		 * @param b b iterator
		 */
		inline friend bool operator== (const Iterator<IT, IV>& a, const Iterator<IT, IV>& b) { return a.ptr == b.ptr; };

		/**
		 * Inequality comparison operator
		 * @param a a iterator
		 * @param b b iterator
		 */
		inline friend bool operator!= (const Iterator<IT, IV>& a, const Iterator<IT, IV>& b) { return a.ptr != b.ptr; };

	private:
		IT* ptr;
	};

	/**
	 * unique_ptr sequence iterator
	 * @param sequenceBegin pointer to first element
	 * @param sequenceEnd pointer to last + 1 element
	 */
	inline UniquePtrSequenceIterator(unique_ptr<T>* sequenceBegin, unique_ptr<T>* sequenceEnd): sequenceBegin(sequenceBegin), sequenceEnd(sequenceEnd) {}

	/**
	 * @returns begin iterator
	 */
	inline Iterator<unique_ptr<T>, T> begin() { return Iterator<unique_ptr<T>, T>(sequenceBegin); }

	/**
	 * @returns end iterator
	 */
	inline Iterator<unique_ptr<T>, T> end() { return Iterator<unique_ptr<T>, T>(sequenceEnd); }

private:
	unique_ptr<T>* sequenceBegin;
	unique_ptr<T>* sequenceEnd;
};

/**
 * Const unique_ptr sequence iterator
 * @author Andreas Drewke
 */
template<typename T>
struct ConstUniquePtrSequenceIterator {

	/**
	 * Iterator for unique_ptr sequence iterator
	 * @author Andreas Drewke
	 */
	template<typename IT, typename IV>
	struct Iterator
	{
		// see: https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
		using iterator_category = forward_iterator_tag;
		using difference_type = ptrdiff_t;
		using value_type = IV*;
		using pointer = IV*;
		using reference = IV*;

		/**
		 * Constructor
		 * @param ptr pointer to container element
		 */
		inline Iterator(const IT* ptr) : ptr(ptr) {}

		/**
		 * @returns access iterator '*'
		 */
		inline reference operator*() const { return ptr->get(); }

		/**
		 * @returns access iterator '->'
		 */
		inline pointer operator->() const { return ptr->get(); }

		/**
		 * @returns prefix incremented iterator
		 */
		inline Iterator<IT, IV>& operator++() { ptr++; return *this; }

		/**
		 * @returns postfix incremented iterator
		 */
		inline Iterator<IT, IV> operator++(int) { auto tmp = *this; ++(*this); return tmp; }

		/**
		 * Equality comparison operator
		 * @param a a iterator
		 * @param b b iterator
		 */
		inline friend bool operator== (const Iterator<IT, IV>& a, const Iterator<IT, IV>& b) { return a.ptr == b.ptr; };

		/**
		 * Inequality comparison operator
		 * @param a a iterator
		 * @param b b iterator
		 */
		inline friend bool operator!= (const Iterator<IT, IV>& a, const Iterator<IT, IV>& b) { return a.ptr != b.ptr; };

	private:
		const IT* ptr;
	};

	/**
	 * Const unique_ptr sequence iterator
	 * @param sequenceBegin pointer to first element
	 * @param sequenceEnd pointer to last + 1 element
	 */
	inline ConstUniquePtrSequenceIterator(const unique_ptr<T>* sequenceBegin, const unique_ptr<T>* sequenceEnd): sequenceBegin(sequenceBegin), sequenceEnd(sequenceEnd) {}

	/**
	 * @returns begin iterator
	 */
	inline Iterator<const unique_ptr<T>, const T> begin() { return Iterator<const unique_ptr<T>, const T>(sequenceBegin); }

	/**
	 * @returns end iterator
	 */
	inline Iterator<const unique_ptr<T>, const T> end() { return Iterator<const unique_ptr<T>, const T>(sequenceEnd); }

private:
	const unique_ptr<T>* sequenceBegin;
	const unique_ptr<T>* sequenceEnd;
};

};
};
