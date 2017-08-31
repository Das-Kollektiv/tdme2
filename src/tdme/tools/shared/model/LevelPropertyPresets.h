// Generated from /tdme/src/tdme/tools/shared/model/LevelPropertyPresets.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

#include <ext/tinyxml/tinyxml.h>

#include <tdme/tools/shared/model/LevelEditorLight.h>

using std::map;
using std::wstring;
using std::vector;

using java::lang::String;
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
	map<wstring, vector<PropertyModelClass*>> objectPropertiesPresets {  };
	map<wstring, LevelEditorLight*> lightPresets {  };
	static LevelPropertyPresets* instance;

public:

	/** 
	 * @return level editor presets instance
	 */
	static LevelPropertyPresets* getInstance();

	/** 
	 * Set default level properties  
	 * @param level
	 */
	void setDefaultLevelProperties(LevelEditorLevel* level);

public:

	/** 
	 * @return map properties preset
	 */
	const vector<PropertyModelClass*>* getMapPropertiesPreset() const;

	/** 
	 * @return object property presets
	 */
	const map<wstring, vector<PropertyModelClass*>>* getObjectPropertiesPresets() const;

	/** 
	 * @return light presets
	 */
	const map<wstring, LevelEditorLight*>* getLightPresets() const;

private:

	/** 
	 * Returns immediate children by tagnames of parent
	 * @param parent
	 * @param name
	 * @return children with given name
	 */
	const vector<TiXmlElement*> getChildrenByTagName(TiXmlElement* parent, const char* name);

public:
	/**
	 * Constructor
	 * @param path name
	 * @param file name
	 */
	LevelPropertyPresets(String* pathName, String* fileName);
};
