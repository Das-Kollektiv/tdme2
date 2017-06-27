// Generated from /tdme/src/tdme/utils/_Console.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;


struct default_init_tag;

/** 
 * Console 
 * @author Andreas Drewke
 * @versio $Id$
 */
class tdme::utils::_Console
	: public virtual Object
{

public:
	typedef Object super;

	/** 
	 * Print object and trailing newline to console
	 * @param object
	 */
	static void println(Object* object);

	/** 
	 * Print byte and trailing newline to console
	 * @param value
	 */
	static void println(int8_t value);

	/** 
	 * Print short and trailing newline to console
	 * @param value
	 */
	static void println(int16_t value);

	/** 
	 * Print int and trailing newline to console
	 * @param value
	 */
	static void println(int32_t value);

	/** 
	 * Print long and trailing newline to console
	 * @param value
	 */
	static void println(int64_t value);

	/** 
	 * Print float and trailing newline to console
	 * @param value
	 */
	static void println(float value);

	/** 
	 * Print double and trailing newline to console
	 * @param value
	 */
	static void println(double value);

	/** 
	 * Print boolean and trailing newline to console
	 * @param value
	 */
	static void println(bool value);

	/** 
	 * Print char and trailing newline to console
	 * @param value
	 */
	static void println(char16_t value);

	/** 
	 * Print object to console
	 * @param text
	 */
	static void print(Object* object);

	/** 
	 * Print byte to console
	 * @param value
	 */
	static void print(int8_t value);

	/** 
	 * Print short to console
	 * @param value
	 */
	static void print(int16_t value);

	/** 
	 * Print int to console
	 * @param value
	 */
	static void print(int32_t value);

	/** 
	 * Print long to console
	 * @param value
	 */
	static void print(int64_t value);

	/** 
	 * Print float to console
	 * @param value
	 */
	static void print(float value);

	/** 
	 * Print double to console
	 * @param value
	 */
	static void print(double value);

	/** 
	 * Print boolean to console
	 * @param value
	 */
	static void print(bool value);

	/** 
	 * Print char to console
	 * @param value
	 */
	static void print(char16_t value);

	/** 
	 * Print new line to console
	 * @param text
	 */
	static void println();

	// Generated
	_Console();
protected:
	_Console(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
