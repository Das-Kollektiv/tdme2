
#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::vector;
using std::string;

using tdme::tools::shared::model::PropertyModelClass;

/** 
 * Properties
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::ModelProperties
{
public: /* protected */
	map<string, PropertyModelClass*> propertiesByName {  };
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
	virtual PropertyModelClass* getProperty(const string& name);

	/** 
	 * @return property count
	 */
	virtual int32_t getPropertyCount();

	/** 
	 * Get property index
	 * @param name
	 * @return index or -1 if not found
	 */
	virtual int32_t getPropertyIndex(const string& name);

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
	virtual bool addProperty(const string& name, const string& value);

	/** 
	 * Update a property
	 * @param old name
	 * @param name
	 * @param value
	 * @return success
	 */
	virtual bool updateProperty(const string& oldName, const string& name, const string& value);

	/** 
	 * Removes a property
	 * @param property name
	 */
	virtual bool removeProperty(const string& name);

	/**
	 * Public constructor
	 */
	ModelProperties();

	/**
	 * Destructor
	 */
	virtual ~ModelProperties();
};
