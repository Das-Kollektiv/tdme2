
#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

#include <ext/tinyxml/tinyxml.h>

#include <tdme/tools/shared/model/LevelEditorLight.h>

using std::map;
using std::string;
using std::vector;

using tdme::tools::shared::model::LevelEditorLevel;
using tdme::ext::tinyxml::TiXmlElement;

using tdme::tools::shared::model::LevelEditorLight;

/** 
 * Level Property Presets
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelPropertyPresets final
{

private:
	vector<PropertyModelClass*> mapPropertiesPreset {  };
	map<string, vector<PropertyModelClass*>> objectPropertiesPresets {  };
	map<string, LevelEditorLight*> lightPresets {  };
	static LevelPropertyPresets* instance;

public:

	/** 
	 * @return level editor presets instance
	 */
	static LevelPropertyPresets* getInstance();

	/** 
	 * Set default level properties  
	 * @param level level
	 */
	void setDefaultLevelProperties(LevelEditorLevel* level);

public:

	/** 
	 * @return map properties preset
	 */
	const vector<PropertyModelClass*>& getMapPropertiesPreset() const;

	/** 
	 * @return object property presets
	 */
	const map<string, vector<PropertyModelClass*>>* getObjectPropertiesPresets() const;

	/** 
	 * @return light presets
	 */
	const map<string, LevelEditorLight*>& getLightPresets() const;

private:

	/** 
	 * Returns immediate children by tagnames of parent
	 * @param parent parent
	 * @param name name
	 * @return children with given name
	 */
	const vector<TiXmlElement*> getChildrenByTagName(TiXmlElement* parent, const char* name);

public:
	/**
	 * Constructor
	 * @param pathName path name
	 * @param fileName file name
	 */
	LevelPropertyPresets(const string& pathName, const string& fileName);

	/**
	 * Destructor
	 */
	~LevelPropertyPresets();
};
