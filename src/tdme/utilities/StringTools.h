#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::string_view;
using std::vector;

/**
 * String tools class
 * @author Andreas Drewke
 */
class tdme::utilities::StringTools final
{
public:

	/**
	 * UTF8 string character iterator
	 */
	class UTF8CharacterIterator {
	public:
		/**
		 * Public constructor
		 * @param stringReference string reference
		 */
		UTF8CharacterIterator(const string& stringReference): stringReference(stringReference) {
			//
		}

		/**
		 * Reset
		 */
		inline void reset() {
			binaryPosition = 0;
			characterPosition = 0;
		}

		/**
		 * @return underlying binary buffer position
		 */
		inline int getBinaryPosition() {
			return binaryPosition;
		}

		/**
		 * Set underlying binary buffer position
		 * @param position underlying buffer position
		 */
		inline void seekBinaryPosition(int position) {
			while (hasNext() == true && binaryPosition < position) {
				if (hasNext() == true) next();
			}
		}

		/**
		 * @return character position
		 */
		inline int getCharacterPosition() {
			return characterPosition;
		}

		/**
		 * Seek character position
		 * @param characterPosition character position
		 */
		inline void seekCharacterPosition(int characterPosition) {
			if (this->characterPosition > characterPosition) reset();
			auto seekCount = characterPosition - this->characterPosition;
			for (auto i = 0; i < seekCount; i++) {
				if (hasNext() == true) next();
			}
		}

		/**
		 * @return next character available
		 */
		inline bool hasNext() {
			return binaryPosition < stringReference.size();
		}
		/**
		 * @return next character or -1 if an error occurred or no string left
		 */
		int next() {
			// see: http://www.zedwood.com/article/cpp-utf8-char-to-codepoint
			int l = stringReference.size() - binaryPosition;
			if (l < 1) return -1;
			unsigned char u0 = stringReference[binaryPosition + 0];
			if (u0 >= 0 && u0 <= 127) {
				binaryPosition++;
				characterPosition++;
				return u0;
			}
			if (l < 2) {
				binaryPosition++;
				characterPosition++;
				return -1;
			}
			unsigned char u1 = stringReference[binaryPosition + 1];
			if (u0 >= 192 && u0 <= 223) {
				binaryPosition+= 2;
				characterPosition++;
				return (u0 - 192) * 64 + (u1 - 128);
			}
			if (stringReference[binaryPosition + 0] == 0xed && (stringReference[binaryPosition + 1] & 0xa0) == 0xa0) {
				binaryPosition+= 2;
				characterPosition++;
				return -1; // code points, 0xd800 to 0xdfff
			}
			if (l < 3) {
				binaryPosition+= 2;
				characterPosition++;
				return -1;
			}
			unsigned char u2 = stringReference[binaryPosition + 2];
			if (u0 >= 224 && u0 <= 239) {
				binaryPosition+= 3;
				characterPosition++;
				return (u0 - 224) * 4096 + (u1 - 128) * 64 + (u2 - 128);
			}
			if (l < 4) {
				binaryPosition+= 3;
				characterPosition++;
				return -1;
			}
			unsigned char u3 = stringReference[binaryPosition + 3];
			if (u0 >= 240 && u0 <= 247) {
				binaryPosition+= 4;
				characterPosition++;
				return (u0 - 240) * 262144 + (u1 - 128) * 4096 + (u2 - 128) * 64 + (u3 - 128);
			}
			//
			binaryPosition+= 4;
			characterPosition++;
			return -1;
		}

	private:
		const string& stringReference;
		int binaryPosition { 0 };
		int characterPosition { 0 };
	};

	/**
	 * Checks if string starts with prefix
	 * @param src source string
     * @param prefix prefix string
	 * @return bool
	 */
	inline static const bool startsWith(const string& src, const string& prefix) {
		return src.find(prefix) == 0;
	}

	/**
	 * Checks if string starts with prefix
	 * @param src source string
     * @param prefix prefix string
	 * @return bool
	 */
	inline static const bool viewStartsWith(const string_view& src, const string& prefix) {
		return src.find(prefix) == 0;
	}

	/**
	 * Checks if string ends with suffix
	 * @param src source string
     * @param suffix suffix string
	 * @return bool
	 */
	inline static const bool endsWith(const string& src, const string& suffix) {
		return
			src.size() >= suffix.size() &&
			src.compare(src.size() - suffix.size(), suffix.size(), suffix) == 0;
	}

	/**
	 * Checks if string ends with suffix
	 * @param src source string
     * @param suffix suffix string
	 * @return bool
	 */
	inline static const bool viewEndsWith(const string_view& src, const string& suffix) {
		return
			src.size() >= suffix.size() &&
			src.compare(src.size() - suffix.size(), suffix.size(), suffix) == 0;
	}

	/**
	 * Replace char with another char
	 * @param src source string to be processed
	 * @param what what to replace
	 * @param by to replace by
	 * @param beginIndex index to begin with
	 * @return new string
	 */
	static const string replace(const string& src, const char what, const char by, int beginIndex = 0);

	/**
	 * Replace string with another string
	 * @param src source string to be processed
	 * @param what what to replace
	 * @param by to replace by
	 * @param beginIndex index to begin with
	 * @return new string
	 */
	static const string replace(const string& src, const string& what, const string& by, int beginIndex = 0);

	/**
	 * Finds first index of given character
	 * @param src source string
	 * @param what what
	 * @return index or -1 if not found
	 */
	inline static int32_t firstIndexOf(const string& src, char what) {
		return src.find_first_of(what);
	}

	/**
	 * Finds first index of characters provided within given string
	 * @param src source string
	 * @param what what
	 * @return index or -1 if not found
	 */
	inline static int32_t firstIndexOf(const string& src, const string& what) {
		return src.find_first_of(what);
	}

	/**
	 * Finds last index of given character
	 * @param src source string
	 * @param what what
	 * @return index or -1 if not found
	 */
	inline static int32_t lastIndexOf(const string& src, char what) {
		return src.find_last_of(what);
	}

	/**
	 * Finds last index of characters provided within given string
	 * @param src source string
	 * @param what what
	 * @return index or -1 if not found
	 */
	inline static int32_t lastIndexOf(const string& src, const string& what) {
		return src.find_last_of(what);
	}

	/**
	 * Returns substring of given string from begin index
	 * @param src source string
	 * @param beginIndex begin index
	 * @return new string
	 */
	inline static const string substring(const string& src, int32_t beginIndex) {
		return src.substr(beginIndex);
	}

	/**
	 * Returns substring of given string from begin index
	 * @param src source string
	 * @param beginIndex begin index
	 * @return new string
	 */
	inline static const string_view viewSubstring(const string_view& src, int32_t beginIndex) {
		return src.substr(beginIndex);
	}

	/**
	 * Returns substring of given string from begin index to end index
	 * @param src source string
	 * @param beginIndex begin index
	 * @param endIndex end index
	 * @return new string
	 */
	inline static const string substring(const string& src, int32_t beginIndex, int32_t endIndex) {
		return src.substr(beginIndex, endIndex - beginIndex);
	}

	/**
	 * Returns substring of given string from begin index to end index
	 * @param src source string
	 * @param beginIndex begin index
	 * @param endIndex end index
	 * @return new string
	 */
	inline static const string_view viewSubstring(const string_view& src, int32_t beginIndex, int32_t endIndex) {
		return src.substr(beginIndex, endIndex - beginIndex);
	}

	/**
	 * Checks if string equals ignoring case
	 * @param string1 string 1
	 * @param string2 string 2
	 * @return equals
	 */
	static bool equalsIgnoreCase(const string& string1, const string& string2);

	/**
	 * Trim string
	 * @param src source string
	 * @return trimmed string
	 */
	static const string trim(const string& src);

	/**
	 * Trim string
	 * @param src source string
	 * @return trimmed string
	 */
	static const string_view viewTrim(const string_view& src);

	/**
	 * Transform string to lower case
	 * @param src source string
	 * @return transformed string
	 */
	static const string toLowerCase(const string& src);

	/**
	 * Transform string to upper case
	 * @param src source string
	 * @return transformed string
	 */
	static const string toUpperCase(const string& src);

	/**
	 * Do regex pattern matching
	 * @param src source string to test
	 * @param pattern pattern
	 * @return if patter matches
	 */
	static bool regexMatch(const string& src, const string& pattern);

	/**
	 * Replace regex pattern with given string
	 * @param src source string to operate on
	 * @param pattern pattern to search
	 * @param by string that will replace pattern occurrances
	 */
	static const string regexReplace(const string& src, const string& pattern, const string& by);

	/**
	 * Tokenize
	 * @param str string to tokenize
	 * @param delimiters delimiters
	 * @return tokens
	 */
	static const vector<string> tokenize(const string& str, const string& delimiters);

	/**
	 * Get Utf8 string length
	 * @param str string
	 * @return utf8 string length
	 */
	inline static int getUtf8Length(const string& str) {
		UTF8CharacterIterator u8It(str);
		while (u8It.hasNext() == true) u8It.next();
		return u8It.getCharacterPosition();
	}

	/**
	 * Get Utf8 binary buffer index
	 * @param str string
	 * @param charIdx character index
	 * @return UTF binary buffer position from given character/code point index
	 */
	inline static int getUtf8BinaryIndex(const string& str, int charIdx) {
		StringTools::UTF8CharacterIterator u8It(str);
		u8It.seekCharacterPosition(charIdx);
		return u8It.getBinaryPosition();
	}

};

