/**
 * @version $Id: 188570b3834042ce1fe4823beafd44fbea46b5ef $
 */

#include "Array.h"

#include "Value.h"
#include "Grammar.h"
#include "OutputFilter.h"
#include "IndentCanceller.h"

using namespace tdme::ext::jsonbox;

tdme::ext::jsonbox::Array::Array(const allocator_type &alloc) : data(alloc) {
}

tdme::ext::jsonbox::Array::Array(size_type count, const_reference value, const allocator_type &alloc) : data(count, value, alloc) {
}

tdme::ext::jsonbox::Array::Array(const tdme::ext::jsonbox::Array &other) : data(other.data) {
}

tdme::ext::jsonbox::Array &tdme::ext::jsonbox::Array::operator=(const tdme::ext::jsonbox::Array &other) {
	data = other.data;
	return *this;
}

bool tdme::ext::jsonbox::Array::operator==(const tdme::ext::jsonbox::Array &rhs) const {
	return data == rhs.data;
}

bool tdme::ext::jsonbox::Array::operator!=(const tdme::ext::jsonbox::Array &rhs) const {
	return data != rhs.data;
}

bool tdme::ext::jsonbox::Array::operator<(const tdme::ext::jsonbox::Array &rhs) const {
	return data < rhs.data;
}

bool tdme::ext::jsonbox::Array::operator<=(const tdme::ext::jsonbox::Array &rhs) const {
	return data <= rhs.data;
}

bool tdme::ext::jsonbox::Array::operator>(const tdme::ext::jsonbox::Array &rhs) const {
	return data > rhs.data;
}

bool tdme::ext::jsonbox::Array::operator>=(const tdme::ext::jsonbox::Array &rhs) const {
	return data >= rhs.data;
}

void tdme::ext::jsonbox::Array::assign(size_type count, const_reference value) {
	data.assign(count, value);
}

tdme::ext::jsonbox::Array::allocator_type tdme::ext::jsonbox::Array::get_allocator() const {
	return data.get_allocator();
}

tdme::ext::jsonbox::Array::reference tdme::ext::jsonbox::Array::at(size_type pos) {
	return data.at(pos);
}

tdme::ext::jsonbox::Array::const_reference tdme::ext::jsonbox::Array::at(size_type pos) const {
	return data.at(pos);
}

tdme::ext::jsonbox::Array::reference tdme::ext::jsonbox::Array::operator[](size_type pos) {
	return data[pos];
}

tdme::ext::jsonbox::Array::const_reference tdme::ext::jsonbox::Array::operator[](size_type pos) const {
	return data[pos];
}

tdme::ext::jsonbox::Array::reference tdme::ext::jsonbox::Array::front() {
	return data.front();
}

tdme::ext::jsonbox::Array::const_reference tdme::ext::jsonbox::Array::front() const {
	return data.front();
}

tdme::ext::jsonbox::Array::reference tdme::ext::jsonbox::Array::back() {
	return data.back();
}

tdme::ext::jsonbox::Array::const_reference tdme::ext::jsonbox::Array::back() const {
	return data.back();
}

tdme::ext::jsonbox::Array::iterator tdme::ext::jsonbox::Array::begin() {
	return data.begin();
}

tdme::ext::jsonbox::Array::const_iterator tdme::ext::jsonbox::Array::begin() const {
	return data.begin();
}

tdme::ext::jsonbox::Array::iterator tdme::ext::jsonbox::Array::end() {
	return data.end();
}

tdme::ext::jsonbox::Array::const_iterator tdme::ext::jsonbox::Array::end() const {
	return data.end();
}

tdme::ext::jsonbox::Array::reverse_iterator tdme::ext::jsonbox::Array::rbegin() {
	return data.rbegin();
}

tdme::ext::jsonbox::Array::const_reverse_iterator tdme::ext::jsonbox::Array::rbegin() const {
	return data.rbegin();
}

tdme::ext::jsonbox::Array::reverse_iterator tdme::ext::jsonbox::Array::rend() {
	return data.rend();
}

tdme::ext::jsonbox::Array::const_reverse_iterator tdme::ext::jsonbox::Array::rend() const {
	return data.rend();
}

bool tdme::ext::jsonbox::Array::empty() const {
	return data.empty();
}

tdme::ext::jsonbox::Array::size_type tdme::ext::jsonbox::Array::size() const {
	return data.size();
}

tdme::ext::jsonbox::Array::size_type tdme::ext::jsonbox::Array::max_size() const {
	return data.max_size();
}

void tdme::ext::jsonbox::Array::reserve(size_type size) {
	data.reserve(size);
}

tdme::ext::jsonbox::Array::size_type tdme::ext::jsonbox::Array::capacity() const {
	return data.capacity();
}

void tdme::ext::jsonbox::Array::clear() {
	data.clear();
}

tdme::ext::jsonbox::Array::iterator tdme::ext::jsonbox::Array::insert(iterator pos, const_reference value) {
	return data.insert(pos, value);
}

void tdme::ext::jsonbox::Array::insert(iterator pos, size_type count, const_reference value) {
	data.insert(pos, count, value);
}

tdme::ext::jsonbox::Array::iterator tdme::ext::jsonbox::Array::erase(iterator pos) {
	return data.erase(pos);
}

tdme::ext::jsonbox::Array::iterator tdme::ext::jsonbox::Array::erase(iterator first, iterator last) {
	return data.erase(first, last);
}

void tdme::ext::jsonbox::Array::push_back(const_reference value) {
	data.push_back(value);
}

void tdme::ext::jsonbox::Array::pop_back() {
	data.pop_back();
}

void tdme::ext::jsonbox::Array::resize(size_type count, const_reference value) {
	data.resize(count, value);
}

void tdme::ext::jsonbox::Array::swap(tdme::ext::jsonbox::Array &other) {
	data.swap(other.data);
}

std::ostream& tdme::ext::jsonbox::operator<<(std::ostream &output, const tdme::ext::jsonbox::Array &a) {
	if (a.empty()) {
		output << Structural::BEGIN_ARRAY << Structural::END_ARRAY;

	} else {
		output << Structural::BEGIN_ARRAY;

		OutputFilter<IndentCanceller> indentCanceller(output.rdbuf());
		output.rdbuf(&indentCanceller);

		for (tdme::ext::jsonbox::Array::const_iterator i = a.begin(); i != a.end(); ++i) {
			if (i != a.begin()) {
				output << Structural::VALUE_SEPARATOR;
			}

			output << *i;
		}

		output.rdbuf(indentCanceller.getDestination());
		output << Structural::END_ARRAY;
	}

	return output;
}
