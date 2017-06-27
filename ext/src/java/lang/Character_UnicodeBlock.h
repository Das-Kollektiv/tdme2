// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Character_Subset.h>

using java::lang::Character_Subset;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using java::util::Map;
using java::lang::Character_UnicodeBlock;
using java::lang::Object;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Character_Subset, ObjectArray > Character_SubsetArray;
typedef ::SubArray< ::java::lang::Character_UnicodeBlock, Character_SubsetArray > Character_UnicodeBlockArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::Character_SubsetArray;
using java::lang::Character_UnicodeBlockArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

struct default_init_tag;
class java::lang::Character_UnicodeBlock final
	: public Character_Subset
{

public:
	typedef Character_Subset super;
	static Character_UnicodeBlock* AEGEAN_NUMBERS;
	static Character_UnicodeBlock* ALPHABETIC_PRESENTATION_FORMS;
	static Character_UnicodeBlock* ARABIC;
	static Character_UnicodeBlock* ARABIC_PRESENTATION_FORMS_A;
	static Character_UnicodeBlock* ARABIC_PRESENTATION_FORMS_B;
	static Character_UnicodeBlock* ARMENIAN;
	static Character_UnicodeBlock* ARROWS;
	static Character_UnicodeBlock* BASIC_LATIN;
	static Character_UnicodeBlock* BENGALI;
	static Character_UnicodeBlock* BLOCK_ELEMENTS;
	static Character_UnicodeBlock* BOPOMOFO;
	static Character_UnicodeBlock* BOPOMOFO_EXTENDED;
	static Character_UnicodeBlock* BOX_DRAWING;
	static Character_UnicodeBlock* BRAILLE_PATTERNS;
	static Character_UnicodeBlock* BUHID;
	static Character_UnicodeBlock* BYZANTINE_MUSICAL_SYMBOLS;
	static Character_UnicodeBlock* CHEROKEE;
	static Character_UnicodeBlock* CJK_COMPATIBILITY;
	static Character_UnicodeBlock* CJK_COMPATIBILITY_FORMS;
	static Character_UnicodeBlock* CJK_COMPATIBILITY_IDEOGRAPHS;
	static Character_UnicodeBlock* CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT;
	static Character_UnicodeBlock* CJK_RADICALS_SUPPLEMENT;
	static Character_UnicodeBlock* CJK_SYMBOLS_AND_PUNCTUATION;
	static Character_UnicodeBlock* CJK_UNIFIED_IDEOGRAPHS;
	static Character_UnicodeBlock* CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A;
	static Character_UnicodeBlock* CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B;
	static Character_UnicodeBlock* COMBINING_DIACRITICAL_MARKS;
	static Character_UnicodeBlock* COMBINING_HALF_MARKS;
	static Character_UnicodeBlock* COMBINING_MARKS_FOR_SYMBOLS;
	static Character_UnicodeBlock* CONTROL_PICTURES;
	static Character_UnicodeBlock* CURRENCY_SYMBOLS;
	static Character_UnicodeBlock* CYPRIOT_SYLLABARY;
	static Character_UnicodeBlock* CYRILLIC;
	static Character_UnicodeBlock* CYRILLIC_SUPPLEMENTARY;
	static Character_UnicodeBlock* DESERET;
	static Character_UnicodeBlock* DEVANAGARI;
	static Character_UnicodeBlock* DINGBATS;
	static Character_UnicodeBlock* ENCLOSED_ALPHANUMERICS;
	static Character_UnicodeBlock* ENCLOSED_CJK_LETTERS_AND_MONTHS;
	static Character_UnicodeBlock* ETHIOPIC;
	static Character_UnicodeBlock* GENERAL_PUNCTUATION;
	static Character_UnicodeBlock* GEOMETRIC_SHAPES;
	static Character_UnicodeBlock* GEORGIAN;
	static Character_UnicodeBlock* GOTHIC;
	static Character_UnicodeBlock* GREEK;
	static Character_UnicodeBlock* GREEK_EXTENDED;
	static Character_UnicodeBlock* GUJARATI;
	static Character_UnicodeBlock* GURMUKHI;
	static Character_UnicodeBlock* HALFWIDTH_AND_FULLWIDTH_FORMS;
	static Character_UnicodeBlock* HANGUL_COMPATIBILITY_JAMO;
	static Character_UnicodeBlock* HANGUL_JAMO;
	static Character_UnicodeBlock* HANGUL_SYLLABLES;
	static Character_UnicodeBlock* HANUNOO;
	static Character_UnicodeBlock* HEBREW;
	static Character_UnicodeBlock* HIGH_PRIVATE_USE_SURROGATES;
	static Character_UnicodeBlock* HIGH_SURROGATES;
	static Character_UnicodeBlock* HIRAGANA;
	static Character_UnicodeBlock* IDEOGRAPHIC_DESCRIPTION_CHARACTERS;
	static Character_UnicodeBlock* IPA_EXTENSIONS;
	static Character_UnicodeBlock* KANBUN;
	static Character_UnicodeBlock* KANGXI_RADICALS;
	static Character_UnicodeBlock* KANNADA;
	static Character_UnicodeBlock* KATAKANA;
	static Character_UnicodeBlock* KATAKANA_PHONETIC_EXTENSIONS;
	static Character_UnicodeBlock* KHMER;
	static Character_UnicodeBlock* KHMER_SYMBOLS;
	static Character_UnicodeBlock* LAO;
	static Character_UnicodeBlock* LATIN_1_SUPPLEMENT;
	static Character_UnicodeBlock* LATIN_EXTENDED_A;
	static Character_UnicodeBlock* LATIN_EXTENDED_ADDITIONAL;
	static Character_UnicodeBlock* LATIN_EXTENDED_B;
	static Character_UnicodeBlock* LETTERLIKE_SYMBOLS;
	static Character_UnicodeBlock* LIMBU;
	static Character_UnicodeBlock* LINEAR_B_IDEOGRAMS;
	static Character_UnicodeBlock* LINEAR_B_SYLLABARY;
	static Character_UnicodeBlock* LOW_SURROGATES;
	static Character_UnicodeBlock* MALAYALAM;
	static Character_UnicodeBlock* MATHEMATICAL_ALPHANUMERIC_SYMBOLS;
	static Character_UnicodeBlock* MATHEMATICAL_OPERATORS;
	static Character_UnicodeBlock* MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A;
	static Character_UnicodeBlock* MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B;
	static Character_UnicodeBlock* MISCELLANEOUS_SYMBOLS;
	static Character_UnicodeBlock* MISCELLANEOUS_SYMBOLS_AND_ARROWS;
	static Character_UnicodeBlock* MISCELLANEOUS_TECHNICAL;
	static Character_UnicodeBlock* MONGOLIAN;
	static Character_UnicodeBlock* MUSICAL_SYMBOLS;
	static Character_UnicodeBlock* MYANMAR;
	static Character_UnicodeBlock* NUMBER_FORMS;
	static Character_UnicodeBlock* OGHAM;
	static Character_UnicodeBlock* OLD_ITALIC;
	static Character_UnicodeBlock* OPTICAL_CHARACTER_RECOGNITION;
	static Character_UnicodeBlock* ORIYA;
	static Character_UnicodeBlock* OSMANYA;
	static Character_UnicodeBlock* PHONETIC_EXTENSIONS;
	static Character_UnicodeBlock* PRIVATE_USE_AREA;
	static Character_UnicodeBlock* RUNIC;
	static Character_UnicodeBlock* SHAVIAN;
	static Character_UnicodeBlock* SINHALA;
	static Character_UnicodeBlock* SMALL_FORM_VARIANTS;
	static Character_UnicodeBlock* SPACING_MODIFIER_LETTERS;
	static Character_UnicodeBlock* SPECIALS;
	static Character_UnicodeBlock* SUPERSCRIPTS_AND_SUBSCRIPTS;
	static Character_UnicodeBlock* SUPPLEMENTAL_ARROWS_A;
	static Character_UnicodeBlock* SUPPLEMENTAL_ARROWS_B;
	static Character_UnicodeBlock* SUPPLEMENTAL_MATHEMATICAL_OPERATORS;
	static Character_UnicodeBlock* SUPPLEMENTARY_PRIVATE_USE_AREA_A;
	static Character_UnicodeBlock* SUPPLEMENTARY_PRIVATE_USE_AREA_B;
	static Character_UnicodeBlock* SURROGATES_AREA;
	static Character_UnicodeBlock* SYRIAC;
	static Character_UnicodeBlock* TAGALOG;
	static Character_UnicodeBlock* TAGBANWA;
	static Character_UnicodeBlock* TAGS;
	static Character_UnicodeBlock* TAI_LE;
	static Character_UnicodeBlock* TAI_XUAN_JING_SYMBOLS;
	static Character_UnicodeBlock* TAMIL;
	static Character_UnicodeBlock* TELUGU;
	static Character_UnicodeBlock* THAANA;
	static Character_UnicodeBlock* THAI;
	static Character_UnicodeBlock* TIBETAN;
	static Character_UnicodeBlock* UGARITIC;
	static Character_UnicodeBlock* UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS;
	static Character_UnicodeBlock* VARIATION_SELECTORS;
	static Character_UnicodeBlock* VARIATION_SELECTORS_SUPPLEMENT;
	static Character_UnicodeBlock* YIJING_HEXAGRAM_SYMBOLS;
	static Character_UnicodeBlock* YI_RADICALS;
	static Character_UnicodeBlock* YI_SYLLABLES;

private:
	static int32_tArray* blockStarts;
	static Character_UnicodeBlockArray* blocks;
	static Map* map;

	/*void ctor(String* arg0); (private) */
	/*void ctor(String* arg0, String* arg1); (private) */
	/*void ctor(String* arg0, StringArray* arg1); (private) */

public:
	static Character_UnicodeBlock* forName(String* arg0);
	static Character_UnicodeBlock* of(char16_t arg0);
	static Character_UnicodeBlock* of(int32_t arg0);

	// Generated
	Character_UnicodeBlock();
protected:
	Character_UnicodeBlock(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
