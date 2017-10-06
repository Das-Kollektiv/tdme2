
#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;

/** 
 * Key
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::Key final
	: public Object
{

public:
	typedef Object super;

private:
	static constexpr int32_t LENGTH_MAX { 512 };
	int32_t length {  };
	int32_t hash {  };
	char16_tArray* data {  };
protected:

	/** 
	 * Constructor
	 */
	void ctor();

public:

	/** 
	 * Reset
	 */
	void reset();

	/** 
	 * Append string
	 * @param string
	 */
	void append(String* string);

	/** 
	 * Append float value
	 * @param value
	 */
	void append(float value);

	/** 
	 * Append int value
	 * @param value
	 */
	void append(int32_t value);
	int32_t hashCode() override;
	bool equals(Object* object) override;

	/** 
	 * Clones this key into key2
	 * @param key 2
	 */
	void cloneInto(Key* key2);

	/** 
	 * @return key data
	 */
	char16_tArray* getData();

	/** 
	 * @return key length
	 */
	int32_t getLength();
	String* toString() override;

	// Generated
	Key();
protected:
	Key(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
