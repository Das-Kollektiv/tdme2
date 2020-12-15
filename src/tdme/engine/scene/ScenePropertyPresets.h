#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

#include <ext/tinyxml/tinyxml.h>

#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/scene/SceneLight.h>

using std::map;
using std::string;
using std::vector;

using tinyxml::TiXmlElement;

using tdme::engine::prototype::PrototypeProperties;
using tdme::engine::prototype::PrototypeProperty;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneLight;
using tdme::engine::scene::ScenePropertyPresets;

/**
 * Level Property Presets
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::scene::ScenePropertyPresets final
{

private:
	vector<PrototypeProperty*> mapPropertiesPreset;
	map<string, vector<PrototypeProperty*>> objectPropertiesPresets;
	map<string, SceneLight*> lightPresets;
	static ScenePropertyPresets* instance;

public:
	/**
	 * Constructor
	 * @param pathName path name
	 * @param fileName file name
	 */
	ScenePropertyPresets(const string& pathName, const string& fileName);

	/**
	 * Destructor
	 */
	~ScenePropertyPresets();

	/**
	 * @return level editor presets instance
	 */
	static ScenePropertyPresets* getInstance();

	/**
	 * Set default level properties
	 * @param level level
	 */
	void setDefaultLevelProperties(Scene* level);

	/**
	 * @return map properties preset
	 */
	inline const vector<PrototypeProperty*>& getMapPropertiesPreset() const {
		return mapPropertiesPreset;
	}

	/**
	 * @return object property presets
	 */
	inline const map<string, vector<PrototypeProperty*>>& getObjectPropertiesPresets() const {
		return objectPropertiesPresets;
	}

	/**
	 * @return light presets
	 */
	inline const map<string, SceneLight*>& getLightPresets() const {
		return lightPresets;
	}

private:

	/**
	 * Returns immediate children by tagnames of parent
	 * @param parent parent
	 * @param name name
	 * @return children with given name
	 */
	const vector<TiXmlElement*> getChildrenByTagName(TiXmlElement* parent, const char* name);

};
