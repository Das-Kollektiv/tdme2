#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/UTF8CharacterIterator.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::math::Math;
using tdme::utilities::UTF8CharacterIterator;

/**
 * Mutable utf8 aware string class
 * @author Andreas Drewke
 */
class tdme::utilities::MutableString final
{
public:
	/**
	 * Public default constructor
	 */
	inline MutableString() {}

	/**
	 * Public constructor
	 * @param s string
	 */
	inline MutableString(const string& s) {
		data = s;
	}

	/**
	 * Public constructor
	 * @param i integer
	 */
	inline MutableString(int i) {
		set(i);
	}

	/**
	 * Public constructor
	 * @param f f
	 * @param decimals decimals
	 */
	inline MutableString(float f, int32_t decimals = 3) {
		set(f, decimals);
	}

	/**
	 * @return binary size
	 */
	inline int size() const {
		return data.size();
	}

	/**
	 * @return character count
	 */
	inline int length() const {
		if (utf8Length != -1) return utf8Length;
		auto u8It = getUTF8CharacterIterator();
		while (u8It.hasNext() == true) u8It.next();
		utf8Length = u8It.getCharacterPosition();
		return utf8Length;
	}

	/**
	 * Get char at given binary index
	 * @param idx idx
	 * @return char
	 */
	inline char getCharAt(int32_t idx) const {
		if (idx < 0 || idx >= data.size()) return 0;
		return data[idx];
	}

	/**
	 * @return utf 8 character at given character index
	 */
	inline int getUTF8CharAt(int32_t idx) const {
		auto u8It = getUTF8CharacterIterator();
		u8It.seekBinaryPosition(getUtf8BinaryIndex(idx));
		return u8It.hasNext() == true?u8It.next():-1;
	}

	/**
	 * Reset
	 */
	inline MutableString& reset() {
		data.clear();
		cache.binaryCache.clear();
		cache.characterCache.clear();
		return *this;
	}

	/**
	 * Set character
	 * @param c char
	 * @return this mutable string
	 */
	inline MutableString& set(char c) {
		reset();
		append(c);
		return *this;
	}

	/**
	 * Append character
	 * @param c char
	 * @return this mutable string
	 */
	inline MutableString& append(char c) {
		data.push_back(c);
		return *this;
	}

	/**
	 * Insert character c at idx
	 * @param idx index
	 * @param c char
	 * @return this mutable string
	 */
	inline MutableString& insert(int32_t idx, char c) {
		auto binaryIdx = getUtf8BinaryIndex(idx);
		data.insert(binaryIdx, 1, c);
		removeCache(binaryIdx, idx);
		return *this;
	}

	/**
	 * Set string
	 * @param s s
	 * @return this mutable string
	 */
	inline MutableString& set(const string& s) {
		reset();
		append(s);
		return *this;
	}

	/**
	 * Append string
	 * @param s s
	 * @return this mutable string
	 */
	inline MutableString& append(const string& s) {
		data+= s;
		return *this;
	}

	/**
	 * Insert string at idx
	 * @param idx index
	 * @param s string
	 * @return this mutable string
	 */
	inline MutableString& insert(int32_t idx, const string& s) {
		auto binaryIdx = getUtf8BinaryIndex(idx);
		data.insert(binaryIdx, s);
		removeCache(binaryIdx, idx);
		return *this;
	}

	/**
	 * Set mutable string
	 * @param s s
	 * @return this mutable string
	 */
	inline MutableString& set(const MutableString& s) {
		reset();
		append(s);
		return *this;
	}

	/**
	 * Append mutable string
	 * @param s s
	 * @return this mutable string
	 */
	inline MutableString& append(const MutableString& s) {
		data+= s.data;
		return *this;
	}

	/**
	 * Insert mutable string at idx
	 * @param idx index
	 * @param s string
	 * @return this mutable string
	 */
	inline MutableString& insert(int32_t idx, const MutableString& s) {
		auto binaryIdx = getUtf8BinaryIndex(idx);
		insert(binaryIdx, s.data);
		removeCache(binaryIdx, idx);
		return *this;
	}

	/**
	 * Set integer
	 * @param i i
	 * @return this mutable string
	 */
	inline MutableString& set(int32_t i) {
		reset();
		append(i);
		return *this;
	}

	/**
	 * Append integer
	 * @param i i
	 * @return this mutable string
	 */
	inline MutableString& append(int32_t i) {
		data+= to_string(i);
		return *this;
	}

	/**
	 * Insert integer at idx
	 * @param idx index
	 * @param i i
	 * @return this mutable string
	 */
	inline MutableString& insert(int32_t idx, int32_t i) {
		// see: http://stackoverflow.com/questions/7123490/how-compiler-is-converting-integer-to-string-and-vice-versa
		auto negative = false;
		if (i < 0) {
			negative = true;
			i = -i;
		}
		while (true == true) {
			auto remainder = i % 10;
			i = i / 10;
			insert(idx, static_cast< char >(('0' + remainder)));
			if (i == 0) {
				break;
			}
		}
		if (negative == true) {
			insert(idx, '-');
		}
		return *this;
	}

	/**
	 * Set float
	 * @param f f
	 * @param decimals decimals
	 * @return this mutable string
	 */
	inline MutableString& set(float f, int32_t decimals = 3) {
		reset();
		append(f, decimals);
		return *this;
	}

	/**
	 * Append float with given decimals
	 * @param f f
	 * @param decimals decimals
	 * @return this mutable string
	 */
	inline MutableString& append(float f, int32_t decimals = 3) {
		insert(data.size(), f, decimals);
		return *this;
	}

	/**
	 * Insert float at idx
	 * @param idx index
	 * @param f float
	 * @param decimals decimals
	 * @return this mutable string
	 */
	inline MutableString& insert(int32_t idx, float f, int32_t decimals = 3) {
		// see: http://stackoverflow.com/questions/7123490/how-compiler-is-converting-integer-to-string-and-vice-versa
		auto integer = static_cast<int>(f);
		for (auto i = 0; i < decimals; i++) {
			auto integerDecimal = static_cast<int>(((f - integer) * Math::pow(10.0f, static_cast<float>(i) + 1.0f))) - (10 * static_cast<int>(((f - integer) * Math::pow(10.0f, static_cast<float>(i)))));
			insert(idx + i, Math::abs(integerDecimal));
		}
		insert(idx, '.');
		insert(idx, Math::abs(integer));
		if (f < 0.0) insert(idx, '-');
		return *this;
	}

	/**
	 * Remove characters at idx with given length
	 * @param idx idx
	 * @param count length
	 * @param binaryCount count of binary bytes that have been removed
	 * @return this mutable string
	 */
	inline MutableString& remove(int32_t idx, int32_t count, int* binaryCount = nullptr) {

		auto u8It = getUTF8CharacterIterator();
		u8It.seekCharacterPosition(idx);
		auto binaryStartIdx = u8It.getBinaryPosition();
		for (auto i = 0; u8It.hasNext() == true &&i < count; i++) {
			u8It.next();
		}
		auto binaryEndIdx = u8It.getBinaryPosition();
		data.erase(binaryStartIdx, binaryEndIdx - binaryStartIdx);
		removeCache(binaryStartIdx, idx);
		if (binaryCount != nullptr) *binaryCount = binaryEndIdx - binaryStartIdx;
		return *this;
	}

	/**
	 * Returns the character index where string s have been found or -1 if not found
	 * @param s string
	 * @param idx index
	 * @return index where string has been found or -1
	 */
	inline int32_t indexOf(const MutableString& s, int32_t idx) const {
		return data.find(s.data, getUtf8BinaryIndex(idx));
	}

	/**
	 * Returns the character index where string s have been found or -1 if not found
	 * @param s string
	 * @return index where string has been found or -1
	 */
	inline int32_t indexOf(const MutableString& s) const {
		return indexOf(s, 0);
	}

	/**
	 * Replace string with another string
	 * @param what what to replace
	 * @param by to replace by
	 * @param beginIndex index to begin with
	 */
	inline void replace(const string& what, const string& by, int beginIndex = 0) {
		beginIndex = getUtf8BinaryIndex(beginIndex);
		string result = data;
		if (what.empty()) return;
		while ((beginIndex = result.find(what, beginIndex)) != std::string::npos) {
			result.replace(beginIndex, what.length(), by);
			beginIndex += by.length();
		}
		// TODO: could be improved
		cache.binaryCache.clear();
		cache.characterCache.clear();
	}

	/**
	 * @return if mutable string is empty
	 */
	inline bool empty() const {
		return data.empty();
	}

	/**
	 * Equals
	 * @param s2 string 2
	 * @return string 2 equals this string
	 */
	inline bool equals(const string& s2) const {
		return data == s2;
	}

	/**
	 * Equals
	 * @param s2 string 2
	 * @return string 2 equals this string
	 */
	inline bool equals(const MutableString& s2) const {
		return data == s2.data;
	}

	/**
	 * @return string
	 */
	inline const string& getString() const {
		return data;
	}

	/**
	 * @return UTF8 character iterator
	 */
	const UTF8CharacterIterator getUTF8CharacterIterator() const {
		return UTF8CharacterIterator(data, &cache);
	}

	/**
	 * @return Get utf8 binary index
	 * @param idx character index
	 * @return utf8 binary index
	 */
	int getUtf8BinaryIndex(int idx) const {
		auto u8It = getUTF8CharacterIterator();
		u8It.seekCharacterPosition(idx);
		return u8It.getBinaryPosition();
	}

	/**
	 * @return Get utf8 character index
	 * @param idx binary index
	 * @return utf8 character index
	 */
	int getUtf8CharacterIndex(int idx) const {
		auto u8It = getUTF8CharacterIterator();
		u8It.seekBinaryPosition(idx);
		return u8It.getCharacterPosition();
	}

	/**
	 * Clone
	 */
	inline MutableString clone() {
		return MutableString(data);
	}

private:
	string data;
	mutable UTF8CharacterIterator::UTF8PositionCache cache;
	mutable int utf8Length { -1 };

	/**
	 * Remove from cache by binary index
	 * @param idx binary index
	 */
	inline void removeCache(int binaryIdx, int characterIdx) {
		// remove succeeding entries from binary cache
		if (binaryIdx >= UTF8CharacterIterator::UTF8PositionCache::CACHE_ENTRY_SIZE) {
			auto& _cache = cache.binaryCache;
			auto removeFromCacheEntryIdx = (binaryIdx / UTF8CharacterIterator::UTF8PositionCache::CACHE_ENTRY_SIZE) - 1;
			if (removeFromCacheEntryIdx < _cache.size()) {
				_cache.erase(_cache.begin() + removeFromCacheEntryIdx, _cache.end());
			}
		} else {
			cache.binaryCache.clear();
		}
		// remove succeeding entries from character position cache
		if (characterIdx >= UTF8CharacterIterator::UTF8PositionCache::CACHE_ENTRY_SIZE) {
			auto& _cache = cache.characterCache;
			auto removeFromCacheEntryIdx = (characterIdx / UTF8CharacterIterator::UTF8PositionCache::CACHE_ENTRY_SIZE) - 1;
			if (removeFromCacheEntryIdx < _cache.size()) {
				_cache.erase(_cache.begin() + removeFromCacheEntryIdx, _cache.end());
			}
		} else {
			cache.characterCache.clear();
		}
		// we also cache the length
		utf8Length = -1;
	}

};
