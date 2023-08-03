#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

#include <ext/tinyxml/tinyxml.h>

#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/scene/SceneLight.h>

using std::make_unique;
using std::map;
using std::string;
using std::unique_ptr;
using std::vector;

using tinyxml::TiXmlElement;

using tdme::engine::prototype::BaseProperties;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneLight;
using tdme::engine::scene::ScenePropertyPresets;

/**
 * Scene Property Presets
 * @author Andreas Drewke
 */
class tdme::engine::scene::ScenePropertyPresets final
{

private:
	vector<unique_ptr<BaseProperty>> properties;
	vector<BaseProperty*> scenePropertiesPreset;
	map<string, vector<BaseProperty*>> entityPropertiesPresetsMap;
	vector<unique_ptr<SceneLight>> lightPresets;
	map<string, SceneLight*> lightPresetsMap;
	STATIC_DLL_IMPEXT static ScenePropertyPresets* instance;

public:
	// forbid class copy
	FORBID_CLASS_COPY(ScenePropertyPresets)

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
	 * @return scene property presets instance
	 */
	static ScenePropertyPresets* getInstance();

	/**
	 * Set default scene properties
	 * @param scene scene
	 */
	void setDefaultSceneProperties(Scene* scene);

	/**
	 * @return scene properties preset
	 */
	inline const vector<BaseProperty*>& getScenePropertiesPreset() const {
		return scenePropertiesPreset;
	}

	/**
	 * @return entity property presets
	 */
	inline const map<string, vector<BaseProperty*>>& getEntityPropertiesPresets() const {
		return entityPropertiesPresetsMap;
	}

	/**
	 * @return light presets
	 */
	inline const map<string, SceneLight*>& getLightPresets() const {
		return lightPresetsMap;
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
