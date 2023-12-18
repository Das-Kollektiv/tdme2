#include <miniscript/utilities/UTF8StringTools.h>

#include <regex>
#include <string>
#include <string_view>

#include <miniscript/miniscript.h>
#include <miniscript/math/Math.h>
#include <miniscript/utilities/Character.h>
#include <miniscript/utilities/UTF8StringTokenizer.h>
#include <miniscript/utilities/UTF8CharacterIterator.h>

using std::regex;
using std::regex_match;
using std::regex_replace;
using std::string;
using std::string_view;

using miniscript::utilities::UTF8StringTools;

using miniscript::math::Math;
using miniscript::utilities::Character;
using miniscript::utilities::UTF8StringTokenizer;
using miniscript::utilities::UTF8CharacterIterator;

const string UTF8StringTools::replace(
	const string& str,
	const string& what,
	const string& by,
	int64_t beginIndex,
	UTF8CharacterIterator::UTF8PositionCache* cache)
{
	auto binaryBeginIndex = getUTF8BinaryIndex(str, beginIndex, cache);
	//
	string result = str;
	if (what.empty()) return result;
	while ((binaryBeginIndex = result.find(what, binaryBeginIndex)) != string::npos) {
		result.replace(binaryBeginIndex, what.length(), by);
		binaryBeginIndex += by.length();
	}
	return result;
}

int64_t UTF8StringTools::firstIndexOf(
	const string& str,
	const string& what,
	int64_t beginIndex,
	UTF8CharacterIterator::UTF8PositionCache* cache
) {
	// utf8 character iterator
	UTF8CharacterIterator u8It(str, cache);
	u8It.seekCharacterPosition(beginIndex);
	//
	auto index = str.find(what, u8It.getBinaryPosition());
	if (index == string::npos) {
		return string::npos;
	} else {
		u8It.seekBinaryPosition(index);
		return static_cast<int64_t>(u8It.getCharacterPosition());
	}
}

int64_t UTF8StringTools::lastIndexOf(
	const string& str,
	const string& what,
	int64_t endIndex,
	UTF8CharacterIterator::UTF8PositionCache* cache
) {
	// utf8 character iterator
	UTF8CharacterIterator u8It(str, cache);
	if (endIndex == string::npos) endIndex = getLength(str, cache);
	//
	int64_t binaryIndex = 0;
	int64_t index = string::npos;
	while (true == true) {
		auto whatBinaryIndex = str.find(what, binaryIndex);
		if (whatBinaryIndex == string::npos) {
			return index;
		} else {
			u8It.seekBinaryPosition(whatBinaryIndex);
			if (u8It.getCharacterPosition() < endIndex) {
				index = u8It.getCharacterPosition();
				binaryIndex = whatBinaryIndex + what.size();
			} else {
				return index;
			}
		}
	}
	//
	return index;
}

int64_t UTF8StringTools::firstIndexOfChars(const string& str, const string& what, int64_t beginIndex, UTF8CharacterIterator::UTF8PositionCache* strCache, UTF8CharacterIterator::UTF8PositionCache* whatCache) {
	// utf8 character iterator
	UTF8CharacterIterator whatU8It(what, whatCache);
	//
	int64_t index = string::npos;
	while (whatU8It.hasNext() == true) {
		auto whatChar = Character::toString(whatU8It.next());
		auto whatIndex = UTF8StringTools::indexOf(str, whatChar, beginIndex, strCache);
		if (whatIndex != string::npos) index = index == string::npos?whatIndex:(Math::min(index, whatIndex));
	}
	//
	if (index == string::npos) {
		return string::npos;
	} else {
		return index;
	}
}

int64_t UTF8StringTools::lastIndexOfChars(const string& str, const string& what, int64_t endIndex, UTF8CharacterIterator::UTF8PositionCache* strCache, UTF8CharacterIterator::UTF8PositionCache* whatCache) {
	// utf8 character iterator
	UTF8CharacterIterator whatU8It(what, whatCache);
	if (endIndex == string::npos) endIndex = getLength(str, strCache);
	//
	int64_t currentIndex = 0;
	int64_t index = string::npos;
	while (true == true) {
		auto hit = false;
		while (whatU8It.hasNext() == true) {
			auto whatChar = Character::toString(whatU8It.next());
			auto whatIndex = UTF8StringTools::indexOf(str, whatChar, currentIndex, strCache);
			if (whatIndex != string::npos) {
				hit = true;
				index = Math::max(index, whatIndex);
			}
			//
			currentIndex++;
		}
		if (hit == false) break;
	}
	//
	if (index == string::npos) {
		return string::npos;
	} else {
		return index;
	}
}

const string_view UTF8StringTools::viewSubstring(const string_view& str, int64_t beginIndex, int64_t endIndex, UTF8CharacterIterator::UTF8PositionCache* cache) {
	// utf8 character iterator
	UTF8CharacterIterator u8It(str, cache);
	u8It.seekCharacterPosition(beginIndex);
	auto binaryBeginIndex = u8It.getBinaryPosition();
	//
	if (endIndex == string::npos) {
		return str.substr(binaryBeginIndex);
	} else {
		u8It.seekCharacterPosition(endIndex) ;
		auto binaryEndIndex = u8It.getBinaryPosition();
		//
		return str.substr(binaryBeginIndex, binaryEndIndex - binaryBeginIndex);
	}
}

bool UTF8StringTools::equalsIgnoreCase(
	const string& string1,
	const string& string2,
	UTF8CharacterIterator::UTF8PositionCache* string1Cache,
	UTF8CharacterIterator::UTF8PositionCache* string2Cache
) {
	if (getLength(string1, string1Cache) != getLength(string2, string2Cache)) return false;
	// utf8 character iterator
	UTF8CharacterIterator string1U8It(string1, string1Cache);
	UTF8CharacterIterator string2U8It(string1, string2Cache);
	//
	while (true == true) {
		auto string1Next = string1U8It.hasNext();
		auto string2Next = string2U8It.hasNext();
		if (string1Next != string2Next) return false;
		if (string1Next == false) return true;
		auto c1 = Character::toUpperCase(string1U8It.next());
		auto c2 = Character::toUpperCase(string2U8It.next());
		if (c1 != c2) return false;
	}
	//
	return false;
}

const string UTF8StringTools::trim(const string& str, UTF8CharacterIterator::UTF8PositionCache* cache) {
	auto result = viewTrim(string_view(str), cache);
	return string(result.data(), result.size());
}

const string_view UTF8StringTools::viewTrim(const string_view& str, UTF8CharacterIterator::UTF8PositionCache* cache) {
	// utf8 character iterator
	UTF8CharacterIterator u8It(str, cache);
	//
	int64_t firstNonSpace = string::npos;
	int64_t lastNonSpace = string::npos;
	while (u8It.hasNext() == true) {
		auto c = u8It.next();
		if (Character::isSpace(c) == false) {
			if (firstNonSpace == string::npos) firstNonSpace = u8It.getCharacterPosition() - 1;
			lastNonSpace = u8It.getCharacterPosition() - 1;
		}
	}
	//
	if (firstNonSpace == string::npos) return string();
	//
	return viewSubstring(str, firstNonSpace, lastNonSpace + 1);
}

const string UTF8StringTools::toLowerCase(const string& str, UTF8CharacterIterator::UTF8PositionCache* cache) {
	string result;
	// utf8 character iterator
	UTF8CharacterIterator u8It(str, cache);
	//
	while (u8It.hasNext() == true) Character::appendToString(result, Character::toLowerCase(u8It.next()));
	//
	return result;
}

const string UTF8StringTools::toUpperCase(const string& str, UTF8CharacterIterator::UTF8PositionCache* cache) {
	string result;
	// utf8 character iterator
	UTF8CharacterIterator u8It(str, cache);
	//
	while (u8It.hasNext() == true) Character::appendToString(result, Character::toUpperCase(u8It.next()));
	//
	return result;
}

bool UTF8StringTools::regexMatch(const string& str, const string& pattern) {
	// TODO: return found groups
	return regex_match(str, regex(pattern, std::regex::ECMAScript));
}

bool UTF8StringTools::regexSearch(const string& str, const string& pattern) {
	// TODO: return found groups
	return regex_search(str, regex(pattern, std::regex::ECMAScript));
}

const string UTF8StringTools::regexReplace(const string& str, const string& pattern, const string& by) {
	return regex_replace(str, regex(pattern, std::regex::ECMAScript), by);
}

const vector<string> UTF8StringTools::tokenize(const string& str, const string& delimiters, bool emptyTokens) {
	UTF8StringTokenizer t;
	t.tokenize(str, delimiters, emptyTokens);
	return t.getTokens();
}

const string UTF8StringTools::padLeft(const string& str, const string& by, int64_t toLength, UTF8CharacterIterator::UTF8PositionCache* cache) {
	auto result = str;
	while (getLength(result) < toLength) result = by + result;
	return result;
}

const string UTF8StringTools::padRight(const string& str, const string& by, int64_t toLength, UTF8CharacterIterator::UTF8PositionCache* cache) {
	auto result = str;
	UTF8CharacterIterator::UTF8PositionCache resultCache;
	if (cache != nullptr) resultCache = *cache;
	while (getLength(result, &resultCache) < toLength) result = result + by;
	return result;
}

int64_t UTF8StringTools::getLength(const string& str, UTF8CharacterIterator::UTF8PositionCache* cache) {
	UTF8CharacterIterator u8It(str, cache);
	u8It.seekCharacterPosition(4611686018427387903); // 2 ^ 62 - 1
	return u8It.getCharacterPosition();
}

const string UTF8StringTools::getCharAt(const string& str, int64_t index, UTF8CharacterIterator::UTF8PositionCache* cache) {
	// utf8 character iterator
	UTF8CharacterIterator u8It(str, cache);
	u8It.seekCharacterPosition(index);
	//
	return u8It.hasNext() == true?Character::toString(u8It.next()):string();
}

int64_t UTF8StringTools::getUTF8BinaryIndex(const string& str, int64_t charIdx, UTF8CharacterIterator::UTF8PositionCache* cache) {
	UTF8CharacterIterator u8It(str, cache);
	u8It.seekCharacterPosition(charIdx);
	return u8It.getBinaryPosition();
}
