// Generated from /tdme/src/tdme/tools/shared/model/ModelProperties.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::vector;
using std::wstring;

using java::lang::Iterable;
using java::lang::String;
using tdme::tools::shared::model::PropertyModelClass;

/** 
 * Properties
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::ModelProperties
{
public: /* protected */
	map<wstring, PropertyModelClass*> propertiesByName {  };
	vector<PropertyModelClass*> properties {  };

public:

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

	/**
	 * Public constructor
	 */
	ModelProperties();
};
