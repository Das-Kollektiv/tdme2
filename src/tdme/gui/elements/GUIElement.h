#pragma once

#include <map>
#include <string>

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::wstring;

using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;


struct default_init_tag;

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
	virtual const wstring& getName() = 0;

	/** 
	 * @return template
	 */
	virtual const wstring& getTemplate() = 0;

	/** 
	 * Get default attributes
	 * @param screen node
	 * @return default attributes
	 */
	virtual map<wstring, wstring>* getAttributes(GUIScreenNode* screenNode) = 0;

	/** 
	 * Create controller which is attached to this node
	 * @param node
	 * @return
	 */
	virtual GUINodeController* createController(GUINode* node) = 0;

	// Generated
	GUIElement();
protected:
	GUIElement(const ::default_init_tag&);
};
