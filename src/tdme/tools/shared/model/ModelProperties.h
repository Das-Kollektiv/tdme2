// Generated from /tdme/src/tdme/tools/shared/model/ModelProperties.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::Iterable;
using java::lang::String;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * Properties
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::ModelProperties
	: public virtual Object
{

public:
	typedef Object super;

public: /* protected */
	_HashMap* propertiesByName {  };
	_ArrayList* properties {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

public:

	/** 
	 * @return properties
	 */
	virtual Iterable* getProperties();

	/** 
	 * Clears properties
	 */
	virtual void clearProperties();

	/** 
	 * Retrieve property by name
	 * @param name
	 * @return property or null
	 */
	virtual PropertyModelClass* getProperty(String* name);

	/** 
	 * @return property count
	 */
	virtual int32_t getPropertyCount();

	/** 
	 * Get property index
	 * @param name
	 * @return index or -1 if not found
	 */
	virtual int32_t getPropertyIndex(String* name);

	/** 
	 * Get property by index
	 * @param idx
	 * @return property or null
	 */
	virtual PropertyModelClass* getPropertyByIndex(int32_t idx);

	/** 
	 * Add a property
	 * @param property
	 */
	virtual bool addProperty(String* name, String* value);

	/** 
	 * Update a property
	 * @param old name
	 * @param name
	 * @param value
	 * @return success
	 */
	virtual bool updateProperty(String* oldName, String* name, String* value);

	/** 
	 * Removes a property
	 * @param property name
	 */
	virtual bool removeProperty(String* name);
	String* toString() override;

	// Generated
	ModelProperties();
protected:
	ModelProperties(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
