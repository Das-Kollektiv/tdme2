// Generated from /tdme/src/tdme/tools/shared/model/LevelPropertyPresets.java

#pragma once

#include <vector>

#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <org/w3c/dom/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

#include <tdme/utils/_HashMap.h>

#include <ext/tinyxml/tinyxml.h>

using std::vector;

using java::lang::Object;
using java::lang::String;
using org::w3c::dom::Element;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;
using tdme::ext::tinyxml::TiXmlElement;


struct default_init_tag;

/** 
 * Level Property Presets
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelPropertyPresets final
	: public Object
{

public:
	typedef Object super;

private:
	_ArrayList* mapPropertiesPreset {  };
	_HashMap* objectPropertiesPresets {  };
	_HashMap* lightPresets {  };
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
protected:

	/** 
	 * Constructor
	 * @throws ParserConfigurationException 
	 * @throws SAXException 
	 */
	void ctor(String* pathName, String* fileName) /* throws(Exception) */;

public:

	/** 
	 * @return map properties preset
	 */
	_ArrayList* getMapPropertiesPreset();

	/** 
	 * @return object property presets
	 */
	_HashMap* getObjectPropertiesPresets();

	/** 
	 * @return light presets
	 */
	_HashMap* getLightPresets();

private:

	/** 
	 * Returns immediate children by tagnames of parent
	 * @param parent
	 * @param name
	 * @return children with given name
	 */
	const vector<TiXmlElement*> getChildrenByTagName(TiXmlElement* parent, const char* name);

	// Generated

public:
	LevelPropertyPresets(String* pathName, String* fileName);
protected:
	LevelPropertyPresets(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
