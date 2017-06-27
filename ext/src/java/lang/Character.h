// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::CharSequence;
using java::lang::Class;
using java::lang::String;


struct default_init_tag;
class java::lang::Character final
	: public virtual Object
	, public Serializable
	, public Comparable
{

public:
	typedef Object super;

public: /* package */
	static bool $assertionsDisabled;

public:
	static constexpr int8_t COMBINING_SPACING_MARK { int8_t(8) };
	static constexpr int8_t CONNECTOR_PUNCTUATION { int8_t(23) };
	static constexpr int8_t CONTROL { int8_t(15) };
	static constexpr int8_t CURRENCY_SYMBOL { int8_t(26) };
	static constexpr int8_t DASH_PUNCTUATION { int8_t(20) };
	static constexpr int8_t DECIMAL_DIGIT_NUMBER { int8_t(9) };
	static constexpr int8_t DIRECTIONALITY_ARABIC_NUMBER { int8_t(6) };
	static constexpr int8_t DIRECTIONALITY_BOUNDARY_NEUTRAL { int8_t(9) };
	static constexpr int8_t DIRECTIONALITY_COMMON_NUMBER_SEPARATOR { int8_t(7) };
	static constexpr int8_t DIRECTIONALITY_EUROPEAN_NUMBER { int8_t(3) };
	static constexpr int8_t DIRECTIONALITY_EUROPEAN_NUMBER_SEPARATOR { int8_t(4) };
	static constexpr int8_t DIRECTIONALITY_EUROPEAN_NUMBER_TERMINATOR { int8_t(5) };
	static constexpr int8_t DIRECTIONALITY_LEFT_TO_RIGHT { int8_t(0) };
	static constexpr int8_t DIRECTIONALITY_LEFT_TO_RIGHT_EMBEDDING { int8_t(14) };
	static constexpr int8_t DIRECTIONALITY_LEFT_TO_RIGHT_OVERRIDE { int8_t(15) };
	static constexpr int8_t DIRECTIONALITY_NONSPACING_MARK { int8_t(8) };
	static constexpr int8_t DIRECTIONALITY_OTHER_NEUTRALS { int8_t(13) };
	static constexpr int8_t DIRECTIONALITY_PARAGRAPH_SEPARATOR { int8_t(10) };
	static constexpr int8_t DIRECTIONALITY_POP_DIRECTIONAL_FORMAT { int8_t(18) };
	static constexpr int8_t DIRECTIONALITY_RIGHT_TO_LEFT { int8_t(1) };
	static constexpr int8_t DIRECTIONALITY_RIGHT_TO_LEFT_ARABIC { int8_t(2) };
	static constexpr int8_t DIRECTIONALITY_RIGHT_TO_LEFT_EMBEDDING { int8_t(16) };
	static constexpr int8_t DIRECTIONALITY_RIGHT_TO_LEFT_OVERRIDE { int8_t(17) };
	static constexpr int8_t DIRECTIONALITY_SEGMENT_SEPARATOR { int8_t(11) };
	static constexpr int8_t DIRECTIONALITY_UNDEFINED { int8_t(-1) };
	static constexpr int8_t DIRECTIONALITY_WHITESPACE { int8_t(12) };
	static constexpr int8_t ENCLOSING_MARK { int8_t(7) };
	static constexpr int8_t END_PUNCTUATION { int8_t(22) };

public: /* package */
	static constexpr int32_t ERROR { -1 };

private:
	static constexpr int32_t FAST_PATH_MAX { 255 };

public:
	static constexpr int8_t FINAL_QUOTE_PUNCTUATION { int8_t(30) };
	static constexpr int8_t FORMAT { int8_t(16) };
	static constexpr int8_t INITIAL_QUOTE_PUNCTUATION { int8_t(29) };
	static constexpr int8_t LETTER_NUMBER { int8_t(10) };
	static constexpr int8_t LINE_SEPARATOR { int8_t(13) };
	static constexpr int8_t LOWERCASE_LETTER { int8_t(2) };
	static constexpr int8_t MATH_SYMBOL { int8_t(25) };
	static constexpr int32_t MAX_CODE_POINT { 1114111 };
	static constexpr char16_t MAX_HIGH_SURROGATE { char16_t(0xdbff) };
	static constexpr char16_t MAX_LOW_SURROGATE { char16_t(0xdfff) };
	static constexpr int32_t MAX_RADIX { 36 };
	static constexpr char16_t MAX_SURROGATE { char16_t(0xdfff) };
	static constexpr char16_t MAX_VALUE { char16_t(0xffff) };
	static constexpr int32_t MIN_CODE_POINT { 0 };
	static constexpr char16_t MIN_HIGH_SURROGATE { char16_t(0xd800) };
	static constexpr char16_t MIN_LOW_SURROGATE { char16_t(0xdc00) };
	static constexpr int32_t MIN_RADIX { 2 };
	static constexpr int32_t MIN_SUPPLEMENTARY_CODE_POINT { 65536 };
	static constexpr char16_t MIN_SURROGATE { char16_t(0xd800) };
	static constexpr char16_t MIN_VALUE { char16_t(0x0000) };
	static constexpr int8_t MODIFIER_LETTER { int8_t(4) };
	static constexpr int8_t MODIFIER_SYMBOL { int8_t(27) };
	static constexpr int8_t NON_SPACING_MARK { int8_t(6) };
	static constexpr int8_t OTHER_LETTER { int8_t(5) };
	static constexpr int8_t OTHER_NUMBER { int8_t(11) };
	static constexpr int8_t OTHER_PUNCTUATION { int8_t(24) };
	static constexpr int8_t OTHER_SYMBOL { int8_t(28) };
	static constexpr int8_t PARAGRAPH_SEPARATOR { int8_t(14) };
	static constexpr int8_t PRIVATE_USE { int8_t(18) };
	static constexpr int32_t SIZE { 16 };
	static constexpr int8_t SPACE_SEPARATOR { int8_t(12) };
	static constexpr int8_t START_PUNCTUATION { int8_t(21) };
	static constexpr int8_t SURROGATE { int8_t(19) };
	static constexpr int8_t TITLECASE_LETTER { int8_t(3) };
	static Class* TYPE;
	static constexpr int8_t UNASSIGNED { int8_t(0) };
	static constexpr int8_t UPPERCASE_LETTER { int8_t(1) };

private:
	static constexpr int64_t serialVersionUID { 3786198910865385080LL };
	char16_t value {  };

protected:
	void ctor(char16_t arg0);

public:
	static int32_t charCount(int32_t arg0);
	char16_t charValue();
	static int32_t codePointAt(CharSequence* arg0, int32_t arg1);
	static int32_t codePointAt(char16_tArray* arg0, int32_t arg1);
	static int32_t codePointAt(char16_tArray* arg0, int32_t arg1, int32_t arg2);

public: /* package */
	static int32_t codePointAtImpl(char16_tArray* arg0, int32_t arg1, int32_t arg2);

public:
	static int32_t codePointBefore(CharSequence* arg0, int32_t arg1);
	static int32_t codePointBefore(char16_tArray* arg0, int32_t arg1);
	static int32_t codePointBefore(char16_tArray* arg0, int32_t arg1, int32_t arg2);

public: /* package */
	static int32_t codePointBeforeImpl(char16_tArray* arg0, int32_t arg1, int32_t arg2);

public:
	static int32_t codePointCount(CharSequence* arg0, int32_t arg1, int32_t arg2);
	static int32_t codePointCount(char16_tArray* arg0, int32_t arg1, int32_t arg2);

public: /* package */
	static int32_t codePointCountImpl(char16_tArray* arg0, int32_t arg1, int32_t arg2);

public:
	int32_t compareTo(Character* arg0);
	static int32_t digit(char16_t arg0, int32_t arg1);
	static int32_t digit(int32_t arg0, int32_t arg1);
	bool equals(Object* arg0) override;
	static char16_t forDigit(int32_t arg0, int32_t arg1);
	static int8_t getDirectionality(char16_t arg0);
	static int8_t getDirectionality(int32_t arg0);
	static int32_t getNumericValue(char16_t arg0);
	static int32_t getNumericValue(int32_t arg0);
	/*static int32_t getPlane(int32_t arg0); (private) */
	static int32_t getType(char16_t arg0);
	static int32_t getType(int32_t arg0);
	int32_t hashCode() override;
	static bool isDefined(char16_t arg0);
	static bool isDefined(int32_t arg0);
	static bool isDigit(char16_t arg0);
	static bool isDigit(int32_t arg0);
	static bool isHighSurrogate(char16_t arg0);
	static bool isISOControl(char16_t arg0);
	static bool isISOControl(int32_t arg0);
	static bool isIdentifierIgnorable(char16_t arg0);
	static bool isIdentifierIgnorable(int32_t arg0);
	static bool isJavaIdentifierPart(char16_t arg0);
	static bool isJavaIdentifierPart(int32_t arg0);
	static bool isJavaIdentifierStart(char16_t arg0);
	static bool isJavaIdentifierStart(int32_t arg0);
	static bool isJavaLetter(char16_t arg0);
	static bool isJavaLetterOrDigit(char16_t arg0);
	static bool isLetter(char16_t arg0);
	static bool isLetter(int32_t arg0);
	static bool isLetterOrDigit(char16_t arg0);
	static bool isLetterOrDigit(int32_t arg0);
	static bool isLowSurrogate(char16_t arg0);
	static bool isLowerCase(char16_t arg0);
	static bool isLowerCase(int32_t arg0);
	static bool isMirrored(char16_t arg0);
	static bool isMirrored(int32_t arg0);
	static bool isSpace(char16_t arg0);
	static bool isSpaceChar(char16_t arg0);
	static bool isSpaceChar(int32_t arg0);
	static bool isSupplementaryCodePoint(int32_t arg0);
	static bool isSurrogatePair(char16_t arg0, char16_t arg1);
	static bool isTitleCase(char16_t arg0);
	static bool isTitleCase(int32_t arg0);
	static bool isUnicodeIdentifierPart(char16_t arg0);
	static bool isUnicodeIdentifierPart(int32_t arg0);
	static bool isUnicodeIdentifierStart(char16_t arg0);
	static bool isUnicodeIdentifierStart(int32_t arg0);
	static bool isUpperCase(char16_t arg0);
	static bool isUpperCase(int32_t arg0);
	static bool isValidCodePoint(int32_t arg0);
	static bool isWhitespace(char16_t arg0);
	static bool isWhitespace(int32_t arg0);
	static int32_t offsetByCodePoints(CharSequence* arg0, int32_t arg1, int32_t arg2);
	static int32_t offsetByCodePoints(char16_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4);

public: /* package */
	static int32_t offsetByCodePointsImpl(char16_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4);

public:
	static char16_t reverseBytes(char16_t arg0);
	static char16_tArray* toChars(int32_t arg0);
	static int32_t toChars(int32_t arg0, char16_tArray* arg1, int32_t arg2);
	static int32_t toCodePoint(char16_t arg0, char16_t arg1);
	static char16_t toLowerCase(char16_t arg0);
	static int32_t toLowerCase(int32_t arg0);
	String* toString() override;
	static String* toString(char16_t arg0);

public: /* package */
	static void toSurrogates(int32_t arg0, char16_tArray* arg1, int32_t arg2);

public:
	static char16_t toTitleCase(char16_t arg0);
	static int32_t toTitleCase(int32_t arg0);
	static char16_t toUpperCase(char16_t arg0);
	static int32_t toUpperCase(int32_t arg0);

public: /* package */
	static char16_tArray* toUpperCaseCharArray(int32_t arg0);
	static int32_t toUpperCaseEx(int32_t arg0);

public:
	static Character* valueOf(char16_t arg0);

	// Generated
	Character(char16_t arg0);
protected:
	Character(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
};
