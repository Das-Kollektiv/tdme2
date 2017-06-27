// Generated from /tdme/src/tdme/tools/shared/model/PropertyModelClass.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;

/** 
 * Property model class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::PropertyModelClass final
	: public Object
{

public:
	typedef Object super;

private:
	String* name {  };
	String* value {  };
protected:

	/** 
	 * Constructor
	 * @param name
	 * @param value
	 */
	void ctor(String* name, String* value);

public:

	/** 
	 * @return name
	 */
	String* getName();

	/** 
	 * Set up name 
	 * @param name
	 */
	void setName(String* name);

	/** 
	 * @return value
	 */
	String* getValue();

	/** 
	 * Set up value
	 * @param value
	 */
	void setValue(String* value);

	/** 
	 * Clones this property model entity
	 */
	PropertyModelClass* clone() override;
	String* toString() override;

	// Generated
	PropertyModelClass(String* name, String* value);
protected:
	PropertyModelClass(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
