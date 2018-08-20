#pragma once

#include <map>
#include <string>

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::string;

using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;

/** 
 * GUI element
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUIElement
{

public:

	/** 
	 * @return name
	 */
	virtual const string& getName() = 0;

	/** 
	 * @return template
	 */
	virtual const string& getTemplate() = 0;

	/** 
	 * Get default attributes
	 * @param screenNode screen node
	 * @return default attributes
	 */
	virtual map<string, string>* getAttributes(GUIScreenNode* screenNode) = 0;

	/** 
	 * Create controller which is attached to this node
	 * @param node node
	 * @return
	 */
	virtual GUINodeController* createController(GUINode* node) = 0;

	GUIElement();
};
