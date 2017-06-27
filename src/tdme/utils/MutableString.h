// Generated from /tdme/src/tdme/utils/MutableString.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;

/** 
 * Mutable string
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::MutableString final
	: public Object
{

public:
	typedef Object super;

private:
	char16_tArray* data {  };
	int32_t length_ {  };
	int32_t hash {  };
protected:

	/** 
	 * Public default constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 */
	void ctor(String* s);

private:

	/** 
	 * Grow string backing array
	 */
	void grow();

public:

	/** 
	 * @return length
	 */
	int32_t length();

	/** 
	 * Get char at index
	 * @param idx
	 * @return char
	 */
	char16_t charAt(int32_t idx);

	/** 
	 * Reset
	 */
	MutableString* reset();

	/** 
	 * Set character
	 * @param c
	 * @return this mutable string
	 */
	MutableString* set(char16_t c);

	/** 
	 * Append character
	 * @param c
	 * @return this mutable string
	 */
	MutableString* append(char16_t c);

	/** 
	 * Insert character c at idx
	 * @param c
	 * @return this mutable string
	 */
	MutableString* insert(int32_t idx, char16_t c);

	/** 
	 * Set string
	 * @param s
	 * @return this mutable string
	 */
	MutableString* set(String* s);

	/** 
	 * Append string
	 * @param s
	 * @return this mutable string
	 */
	MutableString* append(String* s);

	/** 
	 * Insert string at idx
	 * @param c
	 * @return this mutable string
	 */
	MutableString* insert(int32_t idx, String* s);

	/** 
	 * Set mutable string 
	 * @param s
	 * @return this mutable string
	 */
	MutableString* set(MutableString* s);

	/** 
	 * Append mutable string
	 * @param s
	 * @return this mutable string
	 */
	MutableString* append(MutableString* s);

	/** 
	 * Insert mutable string at idx
	 * @param c
	 * @return this mutable string
	 */
	MutableString* insert(int32_t idx, MutableString* s);

	/** 
	 * Set integer
	 * @param i
	 * @return this mutable string
	 */
	MutableString* set(int32_t i);

	/** 
	 * Append integer
	 * @see http://stackoverflow.com/questions/7123490/how-compiler-is-converting-integer-to-string-and-vice-versa
	 * @param i
	 * @return this mutable string
	 */
	MutableString* append(int32_t i);

	/** 
	 * Insert integer at idx
	 * @see http://stackoverflow.com/questions/7123490/how-compiler-is-converting-integer-to-string-and-vice-versa
	 * @param i
	 * @return this mutable string
	 */
	MutableString* insert(int32_t idx, int32_t i);

	/** 
	 * Set float
	 * @param f
	 * @param decimals
	 * @return this mutable string
	 */
	MutableString* set(float f, int32_t decimals);

	/** 
	 * Append float with given decimals
	 * @see http://stackoverflow.com/questions/7123490/how-compiler-is-converting-integer-to-string-and-vice-versa
	 * @param f
	 * @param decimals
	 * @return this mutable string
	 */
	MutableString* append(float f, int32_t decimals);

	/** 
	 * Insert float at idx
	 * @see http://stackoverflow.com/questions/7123490/how-compiler-is-converting-integer-to-string-and-vice-versa
	 * @param i
	 * @return this mutable string
	 */
	MutableString* insert(int32_t idx, float f, int32_t decimals);

	/** 
	 * Delete characters at idx with given length
	 * @param idx
	 * @param length
	 * @return this mutable string
	 */
	MutableString* delete_(int32_t idx, int32_t count);

	/** 
	 * Returns the character index where string s have been found or -1 if not found 
	 * @param string
	 * @param index
	 * @return index where string has been found or -1
	 */
	int32_t indexOf(MutableString* s, int32_t idx);

	/** 
	 * Returns the character index where string s have been found or -1 if not found 
	 * @param string
	 * @return index where string has been found or -1
	 */
	int32_t indexOf(MutableString* s);
	int32_t hashCode() override;

	/** 
	 * Equals 
	 * @param string 2
	 * @return string 2 equals this string
	 */
	bool equals(String* s2);

	/** 
	 * Equals
	 * @param string 2
	 * @return string 2 equals this string
	 */
	bool equals(MutableString* s2);
	String* toString() override;

	// Generated
	MutableString();
	MutableString(String* s);
protected:
	MutableString(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual bool equals(Object* obj);

private:
	virtual ::java::lang::Class* getClass0();
};
